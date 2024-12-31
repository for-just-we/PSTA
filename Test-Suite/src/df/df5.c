/*
 * double free
 * Author: Jiawei Ren
 * Date: 03/02/2022
 */

/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_wchar_t_61a.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-61a.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 61 Data flow: data returned from one function to another in different source files
 *
 * */

#include "std_testcase.h"
#include "aliascheck.h"
#include <wchar.h>

// b file
wchar_t * CWE415_Double_Free__malloc_free_wchar_t_61b_badSource(wchar_t * data)
{
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    return data;
}



/* goodG2B() uses the GoodSource with the BadSink */
wchar_t * CWE415_Double_Free__malloc_free_wchar_t_61b_goodG2BSource(wchar_t * data)
{
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    if (data == NULL) {exit(-1);}
    /* FIX: Do NOT free data in the source - the bad sink frees data */
    return data;
}

/* goodB2G() uses the BadSource with the GoodSink */
wchar_t * CWE415_Double_Free__malloc_free_wchar_t_61b_goodB2GSource(wchar_t * data)
{
    data = (wchar_t *)SAFEMALLOC(100*sizeof(wchar_t));
    if (data == NULL) {exit(-1);}
    /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
    SAFEFREE(data);
    return data;
}


// a file


/* bad function declaration */

void CWE415_Double_Free__malloc_free_wchar_t_61_bad()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = CWE415_Double_Free__malloc_free_wchar_t_61b_badSource(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    DOUBLEFREE(data);
}



/* goodG2B uses the GoodSource with the BadSink */

static void goodG2B()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = CWE415_Double_Free__malloc_free_wchar_t_61b_goodG2BSource(data);
    /* POTENTIAL FLAW: Possibly freeing memory twice */
    SAFEFREE(data);
}

/* goodB2G uses the BadSource with the GoodSink */

static void goodB2G()
{
    wchar_t * data;
    /* Initialize data */
    data = NULL;
    data = CWE415_Double_Free__malloc_free_wchar_t_61b_goodB2GSource(data);
    /* do nothing */
    /* FIX: Don't attempt to free the memory */
    ; /* empty statement needed for some flow variants */
}

void CWE415_Double_Free__malloc_free_wchar_t_61_good()
{
    goodG2B();
    goodB2G();
}


/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */



int main(int argc, char * argv[])
{
    /* seed randomness */
//    srand( (unsigned)time(NULL) );
    CWE415_Double_Free__malloc_free_wchar_t_61_good();
    CWE415_Double_Free__malloc_free_wchar_t_61_bad();
    return 0;
}

