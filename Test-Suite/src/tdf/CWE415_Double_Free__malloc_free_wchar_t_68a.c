/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_wchar_t_68a.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-68a.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 68 Data flow: data passed as a global variable from one function to another in different source files
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

extern wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_badData;
extern wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_goodG2BData;
extern wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_goodB2GData;

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_wchar_t_68b_badSink()
{
    wchar_t * data = CWE415_Double_Free__malloc_free_wchar_t_68_badData;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
void CWE415_Double_Free__malloc_free_wchar_t_68b_goodG2BSink()
{
    wchar_t * data = CWE415_Double_Free__malloc_free_wchar_t_68_goodG2BData;
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE415_Double_Free__malloc_free_wchar_t_68b_goodB2GSink()
{
    wchar_t * data = CWE415_Double_Free__malloc_free_wchar_t_68_goodB2GData;
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

#endif /* OMITGOOD */

wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_badData;
wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_goodG2BData;
wchar_t * CWE415_Double_Free__malloc_free_wchar_t_68_goodB2GData;

#ifndef OMITBAD

/* bad function declaration */
void CWE415_Double_Free__malloc_free_wchar_t_68b_badSink();

void CWE415_Double_Free__malloc_free_wchar_t_68_bad()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)DOUBLEFREEMALLOC(100*sizeof(wchar_t));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_wchar_t_68_badData = data;
    CWE415_Double_Free__malloc_free_wchar_t_68b_badSink();
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* good function declarations */
void CWE415_Double_Free__malloc_free_wchar_t_68b_goodG2BSink();
void CWE415_Double_Free__malloc_free_wchar_t_68b_goodB2GSink();

/* goodG2B uses the GoodSource with the BadSink */
static void goodG2B()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    CWE415_Double_Free__malloc_free_wchar_t_68_goodG2BData = data;
    CWE415_Double_Free__malloc_free_wchar_t_68b_goodG2BSink();
}

/* goodB2G uses the BadSource with the GoodSink */
static void goodB2G()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    CWE415_Double_Free__malloc_free_wchar_t_68_goodB2GData = data;
    CWE415_Double_Free__malloc_free_wchar_t_68b_goodB2GSink();
}

void CWE415_Double_Free__malloc_free_wchar_t_68_good()
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
    CWE415_Double_Free__malloc_free_wchar_t_68_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_wchar_t_68_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
