/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_int64_t_45.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-45.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 45 Data flow: data passed as a static global variable from one function to another in the same source file
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

static int64_t * CWE415_Double_Free__malloc_free_int64_t_45_badData;
static int64_t * CWE415_Double_Free__malloc_free_int64_t_45_goodG2BData;
static int64_t * CWE415_Double_Free__malloc_free_int64_t_45_goodB2GData;

#ifndef OMITBAD

static void badSink()
{
    int64_t * data = CWE415_Double_Free__malloc_free_int64_t_45_badData;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}

void CWE415_Double_Free__malloc_free_int64_t_45_bad()
{
    int64_t * data;
    /* Initialize data */
    data = NULL;
    data = (int64_t *)DOUBLEFREEMALLOC(100*sizeof(int64_t));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_int64_t_45_badData = data;
    badSink();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2BSink()
{
    int64_t * data = CWE415_Double_Free__malloc_free_int64_t_45_goodG2BData;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

static void goodG2B()
{
    int64_t * data;
    /* Initialize data */
    data = NULL;
    data = (int64_t *)SAFEMALLOC(100*sizeof(int64_t));
    if (data == NULL) {exit(-1);}
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    CWE415_Double_Free__malloc_free_int64_t_45_goodG2BData = data;
    goodG2BSink();
}

/* goodB2G() uses the BadSource with the GoodSink */
static void goodB2GSink()
{
    int64_t * data = CWE415_Double_Free__malloc_free_int64_t_45_goodB2GData;
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

static void goodB2G()
{
    int64_t * data;
    /* Initialize data */
    data = NULL;
    data = (int64_t *)SAFEMALLOC(100*sizeof(int64_t));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_int64_t_45_goodB2GData = data;
    goodB2GSink();
}

void CWE415_Double_Free__malloc_free_int64_t_45_good()
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
    CWE415_Double_Free__malloc_free_int64_t_45_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_int64_t_45_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
