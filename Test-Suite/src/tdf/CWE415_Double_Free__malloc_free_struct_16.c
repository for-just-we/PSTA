/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_struct_16.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-16.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 16 Control flow: while(1)
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_struct_16_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    while(1)
    {
        data = (twoIntsStruct *)DOUBLEFREEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
        break;
    }
    while(1)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        DOUBLEFREE(data);
        break;
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G() - use badsource and goodsink by changing the sinks in the second while statement */
static void goodB2G()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    while(1)
    {
        data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
        break;
    }
    while(1)
    {
        /* do nothing */
        /* FIX: Don't attempt to free the memory */
        ; /* empty statement needed for some flow variants */
        break;
    }
}

/* goodG2B() - use goodsource and badsink by changing the sources in the first while statement */
static void goodG2B()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    while(1)
    {
        data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
        if (data == NULL) {exit(-1);}
        /* FIX: Do NOT free data in the source - the bad sink frees data */
        break;
    }
    while(1)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        SAFEFREE(data);
        break;
    }
}

void CWE415_Double_Free__malloc_free_struct_16_good()
{
    goodB2G();
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
    CWE415_Double_Free__malloc_free_struct_16_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_struct_16_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
