/*
 * use after free
 * Author: Jiawei Ren
 * Date: 03/03/2022
 */
#include "aliascheck.h"

/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__return_freed_ptr_09.c
Label Definition File: CWE416_Use_After_Free__return_freed_ptr.label.xml
Template File: point-flaw-09.tmpl.c
*/
/*
 * @description
 * CWE: 416 Use After Free
 * Sinks:
 *    GoodSink: Use a block of memory returned from a function
 *    BadSink : Use a block of memory returned from a function after it has been freed
 * Flow Variant: 09 Control flow: if(GLOBAL_CONST_TRUE) and if(GLOBAL_CONST_FALSE)
 *
 * */

#include "std_testcase.h"

static char * helperBad(char * aString)
{
    size_t i = 0;
    size_t j;
    char * reversedString = NULL;
    if (aString != NULL)
    {
        i = strlen(aString);
        reversedString = (char *) SAFEMALLOC(i+1);
        if (reversedString == NULL) {exit(-1);}
        for (j = 0; j < i; j++)
        {
            reversedString[j] = aString[i-j-1];
        }
        reversedString[i] = '\0';
        /* FLAW: Freeing a memory block and then returning a pointer to the freed memory */
        free(reversedString);
        return reversedString;
    }
    else
    {
        return NULL;
    }
}

static char * helperGood(char * aString)
{
    size_t i = 0;
    size_t j;
    char * reversedString = NULL;
    if (aString != NULL)
    {
        i = strlen(aString);
        reversedString = (char *) SAFEMALLOC(i+1);
        if (reversedString == NULL) {exit(-1);}
        for (j = 0; j < i; j++)
        {
            reversedString[j] = aString[i-j-1];
        }
        reversedString[i] = '\0';
        /* FIX: Do not free the memory before returning */
        return reversedString;
    }
    else
    {
        return NULL;
    }
}

void CWE416_Use_After_Free__return_freed_ptr_09_bad()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            /* Call the bad helper function */
            char * reversedString = helperBad("BadSink");
            UAFFUNC(reversedString);
            /* free(reversedString);
             * This call to free() was removed because we want the tool to detect the use after free,
             * but we don't want that function to be free(). Essentially we want to avoid a double free
             */
        }
    }
}


/* good1() uses if(GLOBAL_CONST_FALSE) instead of if(GLOBAL_CONST_TRUE) */
static void good1()
{
    if(GLOBAL_CONST_FALSE)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        {
            /* Call the good helper function */
            char * reversedString = helperGood("GoodSink");
            SAFEUAFFUNC(reversedString);
            /* free(reversedString);
             * This call to free() was removed because we want the tool to detect the use after free,
             * but we don't want that function to be free(). Essentially we want to avoid a double free
             */
        }
    }
}

/* good2() reverses the bodies in the if statement */
static void good2()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            /* Call the good helper function */
            char * reversedString = helperGood("GoodSink");
            SAFEUAFFUNC(reversedString);
            /* free(reversedString);
             * This call to free() was removed because we want the tool to detect the use after free,
             * but we don't want that function to be free(). Essentially we want to avoid a double free
             */
        }
    }
}

void CWE416_Use_After_Free__return_freed_ptr_09_good()
{
    good1();
    good2();
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */


int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
    CWE416_Use_After_Free__return_freed_ptr_09_good();
    CWE416_Use_After_Free__return_freed_ptr_09_bad();
    return 0;
}

