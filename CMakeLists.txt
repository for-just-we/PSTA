cmake_minimum_required(VERSION 3.23)

project(PSTA
        VERSION 1.0
        DESCRIPTION "Path-sensitive typestate analysis"
        HOMEPAGE_URL "https://github.com/jumormt/Path-Sensitive-Analysis"
        LANGUAGES C CXX
)

# 判断是否定义了 CMAKE_INSTALL_PREFIX
if(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    set(PROJECT_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
else()
    set(PROJECT_SOURCE_ROOT "${CMAKE_INSTALL_PREFIX}")
endif()
message("project source root: ${PROJECT_SOURCE_ROOT}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_CURRENT_SOURCE_DIR}/include/PSTA/config.h @ONLY)

# Check if the LLVM_DIR environment variable is defined and set it accordingly
if (DEFINED LLVM_DIR)
    set(ENV{LLVM_DIR} "${LLVM_DIR}")
elseif (DEFINED ENV{LLVM_DIR})
    set(LLVM_DIR $ENV{LLVM_DIR})
else()
    message(FATAL_ERROR "\
WARNING: The LLVM_DIR var was not set !\n\
Please set this to environment variable to point to the LLVM_DIR directory or set this variable to cmake configuration\n(e.g. on linux: export LLVM_DIR=/path/to/LLVM/dir) \n or \n \n(make the project via: cmake -DLLVM_DIR=your_path_to_LLVM) ")
endif()

if (DEFINED ENV{LLVM_DIR})
    # We need to match the build environment for LLVM:
    # In particular, we need C++11 and the -fno-rtti flag
    set(CMAKE_CXX_STANDARD 17)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_CXX_FLAGS "-fPIC -std=gnu++17 -O0 -fno-rtti -Wno-deprecated")
    else()
        set(CMAKE_CXX_FLAGS "-fPIC -std=gnu++17 -O3 -fno-rtti -Wno-deprecated")
    endif()
    set(CMAKE_C_FLAGS "-fPIC")
endif()


find_package(LLVM REQUIRED CONFIG)
message(STATUS "LLVM STATUS:
  Version       ${LLVM_VERSION}
  Includes      ${LLVM_INCLUDE_DIRS}
  Libraries     ${LLVM_LIBRARY_DIRS}
  Build type    ${LLVM_BUILD_TYPE}
  Dynamic lib   ${LLVM_LINK_LLVM_DYLIB}"
)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

if(NOT "${LLVM_FOUND}")
    message(FATAL_ERROR "Failed to find supported LLVM version")
endif()

# Add LLVM's include directories and link directory for all targets defined hereafter
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Check if LLVM was built generating the single libLLVM.so shared library file or as separate static libraries
if(LLVM_LINK_LLVM_DYLIB)
    message(STATUS "Linking to LLVM dynamic shared library object")
    set(llvm_libs LLVM)
else()
    message(STATUS "Linking to separate LLVM static libraries")
    llvm_map_components_to_libnames(llvm_libs
            bitwriter
            core
            ipo
            irreader
            instcombine
            instrumentation
            target
            linker
            analysis
            scalaropts
            support
    )
endif()

# Make the "add_llvm_library()" command available and configure LLVM/CMake
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
    add_compile_options("-fno-rtti")
endif()

# The same applies for exception handling
if(NOT LLVM_ENABLE_EH)
    add_compile_options("-fno-exceptions")
endif()

# Check if the SVF_DIR environment variable is defined and set it accordingly
if (DEFINED SVF_DIR)
    set(ENV{SVF_DIR} "${SVF_DIR}")
elseif (DEFINED ENV{SVF_DIR})
    set(SVF_DIR $ENV{SVF_DIR})
else()
    message(FATAL_ERROR "\
WARNING: The SVF_DIR var was not set !\n\
Please set this to environment variable to point to the SVF_DIR directory or set this variable to cmake configuration\n
(e.g. on linux: export SVF_DIR=/path/to/SVF/dir) \n or \n \n(make the project via: cmake -DSVF_DIR=your_path_to_SVF) ")
endif()

# Find specifically SVF 2.7 (change if needed) prioritising locations pointed to by $SVF_DIR
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE (STATUS "building SVF in debug mode")
    if (EXISTS "${SVF_DIR}/Debug-build")
        set(SVF_BIN "${SVF_DIR}/Debug-build")
    else()
        set(SVF_BIN "${SVF_DIR}/Release-build")
    endif()
else()
    MESSAGE (STATUS "building SVF in release mode")
    set(SVF_BIN "${SVF_DIR}/Release-build")
endif()

find_package(SVF CONFIG HINTS ${SVF_DIR} ${SVF_BIN})
message(STATUS "SVF STATUS:
    Found:                              ${SVF_FOUND}
    Version:                            ${SVF_VERSION}
    Build mode:                         ${SVF_BUILD_TYPE}
    C++ standard:                       ${SVF_CXX_STANDARD}
    RTTI enabled:                       ${SVF_ENABLE_RTTI}
    Exceptions enabled:                 ${SVF_ENABLE_EXCEPTIONS}
    Install root directory:             ${SVF_INSTALL_ROOT}
    Install binary directory:           ${SVF_INSTALL_BIN_DIR}
    Install library directory:          ${SVF_INSTALL_LIB_DIR}
    Install include directory:          ${SVF_INSTALL_INCLUDE_DIR}
    Install 'extapi.bc' file path:      ${SVF_INSTALL_EXTAPI_FILE}")


# Define the actual runtime executable

# If the SVF CMake package was found, show how to use some "modern" features of this approach; otherwise use old system
if("${SVF_FOUND}")
    message(STATUS "Found installed SVF instance; importing using modern CMake methods")

    # Check that SVF & the found LLVM instance match w.r.t. RTTI/exception handling support
    if(NOT (${SVF_ENABLE_RTTI} STREQUAL ${LLVM_ENABLE_RTTI}))
        message(FATAL_ERROR "SVF & LLVM RTTI support mismatch (SVF: ${SVF_ENABLE_RTTI}, LLVM: ${LLVM_ENABLE_RTTI})!")
    endif()
    if(NOT (${SVF_ENABLE_EXCEPTIONS} STREQUAL ${LLVM_ENABLE_EH}))
        message(FATAL_ERROR "SVF & LLVM exceptions support mismatch (SVF: ${SVF_ENABLE_EXCEPTIONS}, LLVM: ${LLVM_ENABLE_EH})!")
    endif()

    file(GLOB SVF_SHARED_LIBS "${SVF_INSTALL_LIB_DIR}/*.so" "${SVF_INSTALL_LIB_DIR}/*.dylib" "${SVF_INSTALL_LIB_DIR}/*.dll")
    if(SVF_SHARED_LIBS)
        set(SVF_BUILD_STATIC OFF)
    else()
        set(SVF_BUILD_STATIC ON)
    endif()

    message(STATUS "SVF_BUILD_STATIC:                  ${SVF_BUILD_STATIC}")

    # Include SVF's include directories for all targets & include the library directories to find the library objects
    include_directories(SYSTEM ${SVF_INSTALL_INCLUDE_DIR})
    link_directories(${SVF_INSTALL_LIB_DIR})
    # Link the LLVM libraries (single dynamic library/multiple static libraries) to the example executable
else()
    message(STATUS "Failed to find installed SVF instance; using legacy import method")
    message(FATAL_ERROR "SVF & LLVM RTTI support mismatch (SVF: ${SVF_ENABLE_RTTI}, LLVM: ${LLVM_ENABLE_RTTI})!")
endif()

set(SVF_LIB SvfLLVM SvfCore)

# zstd
if(NOT LLVM_LINK_LLVM_DYLIB AND SVF_BUILD_STATIC)
    if(DEFINED ZSTD_PATH)
        message("searching ZSTD in: ${ZSTD_PATH}")
        # If ZSTD_PATH is defined, look for zstd in that directory
        find_library(ZSTD_LIBRARIES NAMES zstd HINTS ${ZSTD_PATH}/lib)
    else()
        # If ZSTD_PATH is not defined, look for zstd in system paths
        find_library(ZSTD_LIBRARIES NAMES zstd)
    endif()
    message("--find zstd lib: ${ZSTD_LIBRARIES}")
    message("--find zstd include: ${ZSTD_INCLUDE_DIRS}")
endif()

# Find Z3 and its include directory from the top-level include file
find_library(
        Z3_LIBRARIES
        REQUIRED
        NAMES z3
        HINTS ${Z3_DIR} ENV Z3_DIR
        PATH_SUFFIXES bin lib)
find_path(
        Z3_INCLUDES
        REQUIRED
        NAMES z3++.h
        HINTS ${Z3_DIR} ENV Z3_DIR
        PATH_SUFFIXES include z3)
message(STATUS "Z3 STATUS:
  Z3 library file:        ${Z3_LIBRARIES}
  Z3 include directory:   ${Z3_INCLUDES}")

# Add the Z3 include directory and link the Z3 library to all targets
link_libraries(${Z3_LIBRARIES})
include_directories(SYSTEM ${Z3_INCLUDES})

# checks if the test-suite is present, if it is then build bc files and add testing to cmake build
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Test-Suite")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Test-Suite)
    enable_testing()
    add_subdirectory(Test-Suite)
    include(CTest)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(tools)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY res/ DESTINATION res)