/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_wchar_t_65a.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-65a.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 65 Data/control flow: data passed as an argument from one function to a function in a different source file called via a function pointer
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

void CWE415_Double_Free__malloc_free_wchar_t_65b_badSink(wchar_t * data)
{
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
void CWE415_Double_Free__malloc_free_wchar_t_65b_goodG2BSink(wchar_t * data)
{
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE415_Double_Free__malloc_free_wchar_t_65b_goodB2GSink(wchar_t * data)
{
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

#endif /* OMITGOOD */

#ifndef OMITBAD

/* bad function declaration */
void CWE415_Double_Free__malloc_free_wchar_t_65b_badSink(wchar_t * data);

void CWE415_Double_Free__malloc_free_wchar_t_65_bad()
{
    wchar_t * data;
    /* define a function pointer */
    void (*funcPtr) (wchar_t *) = CWE415_Double_Free__malloc_free_wchar_t_65b_badSink;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)DOUBLEFREEMALLOC(100*sizeof(wchar_t));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    /* use the function pointer */
    funcPtr(data);
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
void CWE415_Double_Free__malloc_free_wchar_t_65b_goodG2BSink(wchar_t * data);

static void goodG2B()
{
    wchar_t * data;
    void (*funcPtr) (wchar_t *) = CWE415_Double_Free__malloc_free_wchar_t_65b_goodG2BSink;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    funcPtr(data);
}

/* goodB2G uses the BadSource with the GoodSink */
void CWE415_Double_Free__malloc_free_wchar_t_65b_goodB2GSink(wchar_t * data);

static void goodB2G()
{
    wchar_t * data;
    void (*funcPtr) (wchar_t *) = CWE415_Double_Free__malloc_free_wchar_t_65b_goodB2GSink;
    /* Initialize data */
    data = NULL;
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    funcPtr(data);
}

void CWE415_Double_Free__malloc_free_wchar_t_65_good()
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
    CWE415_Double_Free__malloc_free_wchar_t_65_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE415_Double_Free__malloc_free_wchar_t_65_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
