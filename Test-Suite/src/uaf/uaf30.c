/*
 * use after free
 * Author: Jiawei Ren
 * Date: 03/03/2022
 */
#include "aliascheck.h"

/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__malloc_free_long_15.c
Label Definition File: CWE416_Use_After_Free__malloc_free.label.xml
Template File: sources-sinks-15.tmpl.c
*/
/*
 * @description
 * CWE: 416 Use After Free
 * BadSource:  Allocate data using malloc(), initialize memory block, and Deallocate data using free()
 * GoodSource: Allocate data using malloc() and initialize memory block
 * Sinks:
 *    GoodSink: Do nothing
 *    BadSink : Use data
 * Flow Variant: 15 Control flow: switch(6) and switch(7)
 *
 * */

#include "std_testcase.h"

#include <wchar.h>


void CWE416_Use_After_Free__malloc_free_long_15_bad()
{
    long * data;
    /* Initialize data */
    data = NULL;
    switch(6)
    {
        case 6:
            data = (long *)SAFEMALLOC(100*sizeof(long));
            if (data == NULL) {exit(-1);}
            {
                size_t i;
                for(i = 0; i < 100; i++)
                {
                    data[i] = 5L;
                }
            }
            /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
            free(data);
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
    switch(7)
    {
        case 7:
            /* POTENTIAL FLAW: Use of data that may have been freed */
            UAFFUNC(data);
            /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
}



/* goodB2G1() - use badsource and goodsink by changing the second switch to switch(8) */
static void goodB2G1()
{
    long * data;
    /* Initialize data */
    data = NULL;
    switch(6)
    {
        case 6:
            data = (long *)SAFEMALLOC(100*sizeof(long));
            if (data == NULL) {exit(-1);}
            {
                size_t i;
                for(i = 0; i < 100; i++)
                {
                    data[i] = 5L;
                }
            }
            /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
            free(data);
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
    switch(8)
    {
        case 7:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
        default:
            /* FIX: Don't use data that may have been freed already */
            /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
            /* do nothing */
            ; /* empty statement needed for some flow variants */
            break;
    }
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the second switch */
static void goodB2G2()
{
    long * data;
    /* Initialize data */
    data = NULL;
    switch(6)
    {
        case 6:
            data = (long *)SAFEMALLOC(100*sizeof(long));
            if (data == NULL) {exit(-1);}
            {
                size_t i;
                for(i = 0; i < 100; i++)
                {
                    data[i] = 5L;
                }
            }
            /* POTENTIAL FLAW: Free data in the source - the bad sink attempts to use data */
            free(data);
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
    switch(7)
    {
        case 7:
            /* FIX: Don't use data that may have been freed already */
            /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
            /* do nothing */
            ; /* empty statement needed for some flow variants */
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
}

/* goodG2B1() - use goodsource and badsink by changing the first switch to switch(5) */
static void goodG2B1()
{
    long * data;
    /* Initialize data */
    data = NULL;
    switch(5)
    {
        case 6:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
        default:
            data = (long *)SAFEMALLOC(100*sizeof(long));
            if (data == NULL) {exit(-1);}
            {
                size_t i;
                for(i = 0; i < 100; i++)
                {
                    data[i] = 5L;
                }
            }
            /* FIX: Do not free data in the source */
            break;
    }
    switch(7)
    {
        case 7:
            /* POTENTIAL FLAW: Use of data that may have been freed */
            SAFEUAFFUNC(data);
            /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
}

/* goodG2B2() - use goodsource and badsink by reversing the blocks in the first switch */
static void goodG2B2()
{
    long * data;
    /* Initialize data */
    data = NULL;
    switch(6)
    {
        case 6:
            data = (long *)SAFEMALLOC(100*sizeof(long));
            if (data == NULL) {exit(-1);}
            {
                size_t i;
                for(i = 0; i < 100; i++)
                {
                    data[i] = 5L;
                }
            }
            /* FIX: Do not free data in the source */
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
    switch(7)
    {
        case 7:
            /* POTENTIAL FLAW: Use of data that may have been freed */
            SAFEUAFFUNC(data);
            /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not freed */
            break;
        default:
            /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
            printLine("Benign, fixed string");
            break;
    }
}

void CWE416_Use_After_Free__malloc_free_long_15_good()
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
    CWE416_Use_After_Free__malloc_free_long_15_good();
    CWE416_Use_After_Free__malloc_free_long_15_bad();
}
