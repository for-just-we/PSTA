/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_struct_22a.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-22a.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 22 Control flow: Flow controlled by value of a global variable. Sink functions are in a separate file from sources.
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

/* The global variable below is used to drive control flow in the sink function */
extern int CWE415_Double_Free__malloc_free_struct_22_badGlobal;

void CWE415_Double_Free__malloc_free_struct_22_badSink(twoIntsStruct * data)
{
    if(CWE415_Double_Free__malloc_free_struct_22_badGlobal)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        DOUBLEFREE(data);
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* The global variables below are used to drive control flow in the sink functions. */
extern int CWE415_Double_Free__malloc_free_struct_22_goodB2G1Global;
extern int CWE415_Double_Free__malloc_free_struct_22_goodB2G2Global;
extern int CWE415_Double_Free__malloc_free_struct_22_goodG2BGlobal;

/* goodB2G1() - use badsource and goodsink by setting the static variable to false instead of true */
void CWE415_Double_Free__malloc_free_struct_22_goodB2G1Sink(twoIntsStruct * data)
{
    if(CWE415_Double_Free__malloc_free_struct_22_goodB2G1Global)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        /* do nothing */
        /* FIX: Don't attempt to free the memory */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the if in the sink function */
void CWE415_Double_Free__malloc_free_struct_22_goodB2G2Sink(twoIntsStruct * data)
{
    if(CWE415_Double_Free__malloc_free_struct_22_goodB2G2Global)
    {
        /* do nothing */
        /* FIX: Don't attempt to free the memory */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodG2B() - use goodsource and badsink */
void CWE415_Double_Free__malloc_free_struct_22_goodG2BSink(twoIntsStruct * data)
{
    if(CWE415_Double_Free__malloc_free_struct_22_goodG2BGlobal)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        SAFEFREE(data);
    }
}

#endif /* OMITGOOD */

#ifndef OMITBAD

/* The global variable below is used to drive control flow in the sink function */
int CWE415_Double_Free__malloc_free_struct_22_badGlobal = 0;

void CWE415_Double_Free__malloc_free_struct_22_badSink(twoIntsStruct * data);

void CWE415_Double_Free__malloc_free_struct_22_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)DOUBLEFREEMALLOC(100*sizeof(twoIntsStruct));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_struct_22_badGlobal = 1; /* true */
    CWE415_Double_Free__malloc_free_struct_22_badSink(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* The global variables below are used to drive control flow in the sink functions. */
int CWE415_Double_Free__malloc_free_struct_22_goodB2G1Global = 0;
int CWE415_Double_Free__malloc_free_struct_22_goodB2G2Global = 0;
int CWE415_Double_Free__malloc_free_struct_22_goodG2BGlobal = 0;

/* goodB2G1() - use badsource and goodsink by setting the static variable to false instead of true */
void CWE415_Double_Free__malloc_free_struct_22_goodB2G1Sink(twoIntsStruct * data);

static void goodB2G1()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_struct_22_goodB2G1Global = 0; /* false */
    CWE415_Double_Free__malloc_free_struct_22_goodB2G1Sink(data);
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the if in the sink function */
void CWE415_Double_Free__malloc_free_struct_22_goodB2G2Sink(twoIntsStruct * data);

static void goodB2G2()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_struct_22_goodB2G2Global = 1; /* true */
    CWE415_Double_Free__malloc_free_struct_22_goodB2G2Sink(data);
}

/* goodG2B() - use goodsource and badsink */
void CWE415_Double_Free__malloc_free_struct_22_goodG2BSink(twoIntsStruct * data);

static void goodG2B()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    CWE415_Double_Free__malloc_free_struct_22_goodG2BGlobal = 1; /* true */
    CWE415_Double_Free__malloc_free_struct_22_goodG2BSink(data);
}

void CWE415_Double_Free__malloc_free_struct_22_good()
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
    CWE415_Double_Free__malloc_free_struct_22_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_struct_22_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
