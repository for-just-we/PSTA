/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_int_67a.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-67a.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 67 Data flow: data passed in a struct from one function to another in different source files
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

typedef struct _CWE415_Double_Free__malloc_free_int_67_structType
{
    int * structFirst;
} CWE415_Double_Free__malloc_free_int_67_structType;

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_int_67b_badSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct)
{
    int * data = myStruct.structFirst;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
void CWE415_Double_Free__malloc_free_int_67b_goodG2BSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct)
{
    int * data = myStruct.structFirst;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE415_Double_Free__malloc_free_int_67b_goodB2GSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct)
{
    int * data = myStruct.structFirst;
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

#endif /* OMITGOOD */


#ifndef OMITBAD

/* bad function declaration */
void CWE415_Double_Free__malloc_free_int_67b_badSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct);

void CWE415_Double_Free__malloc_free_int_67_bad()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_67_structType myStruct;
    /* Initialize data */
    data = NULL;
    data = (int *)DOUBLEFREEMALLOC(100*sizeof(int));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    myStruct.structFirst = data;
    CWE415_Double_Free__malloc_free_int_67b_badSink(myStruct);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
void CWE415_Double_Free__malloc_free_int_67b_goodG2BSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct);

static void goodG2B()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_67_structType myStruct;
    /* Initialize data */
    data = NULL;
    data = (int *)SAFEMALLOC(100*sizeof(int));
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    myStruct.structFirst = data;
    CWE415_Double_Free__malloc_free_int_67b_goodG2BSink(myStruct);
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE415_Double_Free__malloc_free_int_67b_goodB2GSink(CWE415_Double_Free__malloc_free_int_67_structType myStruct);

static void goodB2G()
{
    int * data;
    CWE415_Double_Free__malloc_free_int_67_structType myStruct;
    /* Initialize data */
    data = NULL;
    data = (int *)SAFEMALLOC(100*sizeof(int));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    myStruct.structFirst = data;
    CWE415_Double_Free__malloc_free_int_67b_goodB2GSink(myStruct);
}

void CWE415_Double_Free__malloc_free_int_67_good()
{
    goodG2B();
    goodB2G();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE415_Double_Free__malloc_free_int_67_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_int_67_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
