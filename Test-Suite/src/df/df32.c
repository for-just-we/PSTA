/*
 * double free
 * Author: Jiawei Ren
 * Date: 03/02/2022
 */


#include "aliascheck.h"


/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE415_Double_Free__malloc_free_long_09.c
Label Definition File: CWE415_Double_Free__malloc_free.label.xml
Template File: sources-sinks-09.tmpl.c
*/
/*
 * @description
 * CWE: 415 Double Free
 * BadSource:  Allocate data using malloc() and Deallocate data using free()
 * GoodSource: Allocate data using malloc()
 * Sinks:
 *    GoodSink: do nothing
 *    BadSink : Deallocate data using free()
 * Flow Variant: 09 Control flow: if(GLOBAL_CONST_TRUE) and if(GLOBAL_CONST_FALSE)
 *
 * */

#include "std_testcase.h"

#include <wchar.h>


void CWE415_Double_Free__malloc_free_long_09_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (long *)SAFEMALLOC(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        DOUBLEFREE(data);
    }
}


/* goodB2G1() - use badsource and goodsink by changing the second GLOBAL_CONST_TRUE to GLOBAL_CONST_FALSE */
static void goodB2G1()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (long *)SAFEMALLOC(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
    }
    if(GLOBAL_CONST_FALSE)
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

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the second if */
static void goodB2G2()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (long *)SAFEMALLOC(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        /* POTENTIAL FLAW: Free data in the source - the bad sink frees data as well */
        SAFEFREE(data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* do nothing */
        /* FIX: Don't attempt to free the memory */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodG2B1() - use goodsource and badsink by changing the first GLOBAL_CONST_TRUE to GLOBAL_CONST_FALSE */
static void goodG2B1()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_FALSE)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        data = (long *)SAFEMALLOC(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        /* FIX: Do NOT free data in the source - the bad sink frees data */
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        SAFEFREE(data);
    }
}

/* goodG2B2() - use goodsource and badsink by reversing the blocks in the first if */
static void goodG2B2()
{
    long * data;
    /* Initialize data */
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (long *)SAFEMALLOC(100*sizeof(long));
        if (data == NULL) {exit(-1);}
        /* FIX: Do NOT free data in the source - the bad sink frees data */
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Possibly freeing memory twice */
        SAFEFREE(data);
    }
}

void CWE415_Double_Free__malloc_free_long_09_good()
{
    goodB2G1();
    goodB2G2();
    goodG2B1();
    goodG2B2();
}


/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
    CWE415_Double_Free__malloc_free_long_09_good();
    CWE415_Double_Free__malloc_free_long_09_bad();
    return 0;
}

