/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE401_Memory_Leak__int_malloc_61a.c
Label Definition File: CWE401_Memory_Leak.c.label.xml
Template File: sources-sinks-61a.tmpl.c
*/
/*
 * @description
 * CWE: 401 Memory Leak
 * BadSource: malloc Allocate data using malloc()
 * GoodSource: Allocate data on the stack
 * Sinks:
 *    GoodSink: call free() on data
 *    BadSink : no deallocation of data
 * Flow Variant: 61 Data flow: data returned from one function to another in different source files
 *
 * */
#include "aliascheck.h"
#include "std_testcase.h"

#include <wchar.h>

#ifndef OMITBAD

int * CWE401_Memory_Leak__int_malloc_61b_badSource(int * data)
{
    /* POTENTIAL FLAW: Allocate memory on the heap */
    data = (int *)NFRMALLOC(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* Initialize and make use of data */
    data[0] = 5;
    printIntLine(data[0]);
    return data;
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B() uses the GoodSource with the BadSink */
int * CWE401_Memory_Leak__int_malloc_61b_goodG2BSource(int * data)
{
    /* FIX: Use memory allocated on the stack with ALLOCA */
    data = (int *)ALLOCA(100*sizeof(int));
    /* Initialize and make use of data */
    data[0] = 5;
    printIntLine(data[0]);
    return data;
}

/* goodB2G() uses the BadSource with the GoodSink */
int * CWE401_Memory_Leak__int_malloc_61b_goodB2GSource(int * data)
{
    /* POTENTIAL FLAW: Allocate memory on the heap */
    data = (int *)SAFEMALLOC(100*sizeof(int));
    if (data == NULL) {exit(-1);}
    /* Initialize and make use of data */
    data[0] = 5;
    printIntLine(data[0]);
    return data;
}

#endif /* OMITGOOD */

#ifndef OMITBAD

/* bad function declaration */
int * CWE401_Memory_Leak__int_malloc_61b_badSource(int * data);

void CWE401_Memory_Leak__int_malloc_61_bad()
{
    int * data;
    data = NULL;
    data = CWE401_Memory_Leak__int_malloc_61b_badSource(data);
    /* POTENTIAL FLAW: No deallocation */
    ; /* empty statement needed for some flow variants */
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B uses the GoodSource with the BadSink */
int * CWE401_Memory_Leak__int_malloc_61b_goodG2BSource(int * data);

static void goodG2B()
{
    int * data;
    data = NULL;
    data = CWE401_Memory_Leak__int_malloc_61b_goodG2BSource(data);
    /* POTENTIAL FLAW: No deallocation */
    ; /* empty statement needed for some flow variants */
}

/* goodB2G uses the BadSource with the GoodSink */
int * CWE401_Memory_Leak__int_malloc_61b_goodB2GSource(int * data);

static void goodB2G()
{
    int * data;
    data = NULL;
    data = CWE401_Memory_Leak__int_malloc_61b_goodB2GSource(data);
    /* FIX: Deallocate memory */
    free(data);
}

void CWE401_Memory_Leak__int_malloc_61_good()
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
    CWE401_Memory_Leak__int_malloc_61_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE401_Memory_Leak__int_malloc_61_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
