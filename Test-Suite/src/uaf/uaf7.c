/*
 * use after free
 * Author: Jiawei Ren
 * Date: 03/03/2022
 */

/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__return_freed_ptr_17.c
Label Definition File: CWE416_Use_After_Free__return_freed_ptr.label.xml
Template File: point-flaw-17.tmpl.c
*/
/*
 * @description
 * CWE: 416 Use After Free
 * Sinks:
 *    GoodSink: Use a block of memory returned from a function
 *    BadSink : Use a block of memory returned from a function after it has been freed
 * Flow Variant: 17 Control flow: for loops
 *
 * */

#include "std_testcase.h"
#include "aliascheck.h"

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
        UAFFUNC(reversedString);
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
        SAFEUAFFUNC(reversedString);
        return reversedString;
    }
    else
    {
        return NULL;
    }
}


void CWE416_Use_After_Free__return_freed_ptr_17_bad()
{
    int j;
    for(j = 0; j < 1; j++)
    {
        {
            /* Call the bad helper function */
            char * reversedString = helperBad("BadSink");
            UAFFUNC(reversedString);
//            printLine(reversedString);
            /* free(reversedString);
             * This call to free() was removed because we want the tool to detect the use after free,
             * but we don't want that function to be free(). Essentially we want to avoid a double free
             */
        }
    }
}


/* good1() uses the GoodSinkBody in the for statements */
static void good1()
{
    int k;
    for(k = 0; k < 1; k++)
    {
        {
            /* Call the good helper function */
            char * reversedString = helperGood("GoodSink");
            SAFEUAFFUNC(reversedString);
//            printLine(reversedString);
            /* free(reversedString);
             * This call to free() was removed because we want the tool to detect the use after free,
             * but we don't want that function to be free(). Essentially we want to avoid a double free
             */
        }
    }
}

void CWE416_Use_After_Free__return_freed_ptr_17_good()
{
    good1();
}

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
    CWE416_Use_After_Free__return_freed_ptr_17_good();
    CWE416_Use_After_Free__return_freed_ptr_17_bad();
    return 0;
}

