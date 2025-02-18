/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE401_Memory_Leak__twoIntsStruct_malloc_22a.c
Label Definition File: CWE401_Memory_Leak.c.label.xml
Template File: sources-sinks-22a.tmpl.c
*/
/*
 * @description
 * CWE: 401 Memory Leak
 * BadSource: malloc Allocate data using malloc()
 * GoodSource: Allocate data on the stack
 * Sinks:
 *    GoodSink: call free() on data
 *    BadSink : no deallocation of data
 * Flow Variant: 22 Control flow: Flow controlled by value of a global variable. Sink functions are in a separate file from sources.
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

/* The global variable below is used to drive control flow in the sink function */
extern int CWE401_Memory_Leak__twoIntsStruct_malloc_22_badGlobal;

void CWE401_Memory_Leak__twoIntsStruct_malloc_22_badSink(twoIntsStruct * data)
{
    if(CWE401_Memory_Leak__twoIntsStruct_malloc_22_badGlobal)
    {
        /* POTENTIAL FLAW: No deallocation */
        ; /* empty statement needed for some flow variants */
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* The global variables below are used to drive control flow in the sink functions. */
extern int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Global;
extern int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Global;
extern int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BGlobal;

/* goodB2G1() - use badsource and goodsink by setting the static variable to false instead of true */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Sink(twoIntsStruct * data)
{
    if(CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Global)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        /* FIX: Deallocate memory */
        free(data);
    }
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the if in the sink function */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Sink(twoIntsStruct * data)
{
    if(CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Global)
    {
        /* FIX: Deallocate memory */
        free(data);
    }
}

/* goodG2B() - use goodsource and badsink */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BSink(twoIntsStruct * data)
{
    if(CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BGlobal)
    {
        /* POTENTIAL FLAW: No deallocation */
        ; /* empty statement needed for some flow variants */
    }
}

#endif /* OMITGOOD */

#ifndef OMITBAD

/* The global variable below is used to drive control flow in the sink function */
int CWE401_Memory_Leak__twoIntsStruct_malloc_22_badGlobal = 0;

void CWE401_Memory_Leak__twoIntsStruct_malloc_22_badSink(twoIntsStruct * data);

void CWE401_Memory_Leak__twoIntsStruct_malloc_22_bad()
{
    twoIntsStruct * data;
    data = NULL;
    /* POTENTIAL FLAW: Allocate memory on the heap */
    data = (twoIntsStruct *)NFRMALLOC(100*sizeof(twoIntsStruct));
    /* Initialize and make use of data */
    data[0].intOne = 0;
    data[0].intTwo = 0;
    printStructLine(&data[0]);
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_badGlobal = 1; /* true */
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_badSink(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* The global variables below are used to drive control flow in the sink functions. */
int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Global = 0;
int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Global = 0;
int CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BGlobal = 0;

/* goodB2G1() - use badsource and goodsink by setting the static variable to false instead of true */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Sink(twoIntsStruct * data);

static void goodB2G1()
{
    twoIntsStruct * data;
    data = NULL;
    /* POTENTIAL FLAW: Allocate memory on the heap */
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    /* Initialize and make use of data */
    data[0].intOne = 0;
    data[0].intTwo = 0;
    printStructLine(&data[0]);
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Global = 0; /* false */
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G1Sink(data);
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the if in the sink function */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Sink(twoIntsStruct * data);

static void goodB2G2()
{
    twoIntsStruct * data;
    data = NULL;
    /* POTENTIAL FLAW: Allocate memory on the heap */
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    /* Initialize and make use of data */
    data[0].intOne = 0;
    data[0].intTwo = 0;
    printStructLine(&data[0]);
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Global = 1; /* true */
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodB2G2Sink(data);
}

/* goodG2B() - use goodsource and badsink */
void CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BSink(twoIntsStruct * data);

static void goodG2B()
{
    twoIntsStruct * data;
    data = NULL;
    /* FIX: Use memory allocated on the stack with ALLOCA */
    data = (twoIntsStruct *)ALLOCA(100*sizeof(twoIntsStruct));
    /* Initialize and make use of data */
    data[0].intOne = 0;
    data[0].intTwo = 0;
    printStructLine(&data[0]);
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BGlobal = 1; /* true */
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_goodG2BSink(data);
}

void CWE401_Memory_Leak__twoIntsStruct_malloc_22_good()
{
    goodB2G1();
    goodB2G2();
    goodG2B();
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
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE401_Memory_Leak__twoIntsStruct_malloc_22_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
