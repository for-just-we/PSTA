/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_struct_18.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-18.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 18 Control flow: goto statements
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_struct_18_bad()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    goto source;
source:
    data = (twoIntsStruct *)DOUBLEFREEMALLOC(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    goto sink;
sink:
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G() - use badsource and goodsink by reversing the blocks on the second goto statement */
static void goodB2G()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    goto source;
source:
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    goto sink;
sink:
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

/* goodG2B() - use goodsource and badsink by reversing the blocks on the first goto statement */
static void goodG2B()
{
    twoIntsStruct * data;
    /* Initialize data */
    data = NULL;
    goto source;
source:
    data = (twoIntsStruct *)SAFEMALLOC(100*sizeof(twoIntsStruct));
    if (data == NULL) {exit(-1);}
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    goto sink;
sink:
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

void CWE415_Double_Free__malloc_free_struct_18_good()
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
    CWE415_Double_Free__malloc_free_struct_18_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_struct_18_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
