#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * taken from by https://www.joelonsoftware.com/2001/12/11/back-to-basics/
 * curious about the value of the pointer maintaining a tail reference
 * in C vs always iterating through to find tail
 * His point is: don't 
 * @param dest - string to copy data to
 * @param src - string to copy data from
 */
char *modstrcat(char *dest, char *src)
{
    while (*dest) dest++;
    while (*dest++ = *src++);
    return --dest;
}

/**
 * calculate difference between two clock times
 * @param start - start time
 * @param end - end time
 * @return double, seconds between the two times
 */
double calcTime(clock_t start, clock_t end)
{
    return ((double)(end - start)) / (CLOCKS_PER_SEC);
}

/**
 * Run a test using standard strcat, from string.h
 * @param - iter int of number of concatenations to perform
 * @return - double of time spent on the test (seconds)
 */
double runStrCatTest(int iter)
{
    double strCatTimeSpent;
    char *initStr = malloc(sizeof(char *) * iter + 1);
    initStr[0] = '\0';
    clock_t strCatBegin = clock();
    for (int i = 0; i < iter; i++)
    {
        strcat(initStr, "a");
    }
    clock_t strCatEnd = clock();
    strCatTimeSpent = calcTime(strCatBegin, strCatEnd);
    free(initStr);
    return strCatTimeSpent;
}

/**
 * Run a test using modified strcat, which returns a pointer to the tail
 * @param - iter int of number of concatenations to perform
 * @return -double of time spent on the test (seconds)
 */
double runMyStrCatTest(int iter)
{
    double strCatTimeSpent;
    char *initStr = malloc(sizeof(char *) * iter + 1);
    initStr[0] = '\0';
    char *p = initStr;
    clock_t myStrCatBegin = clock();
    for (int i = 0; i < iter; i++)
    {
        p = modstrcat(p, "a");
    }
    clock_t myStrCatEnd = clock();
    strCatTimeSpent = calcTime(myStrCatBegin, myStrCatEnd);
    free(initStr);
    return strCatTimeSpent;
}

/**
 * Program to run a certain number of iterations of concatenations
 * using strcat and a modified form of the same.
 */
int main(void)
{
    int n = 1;
    int iters = 20;
    int iterResults[iters];
    double strCatResults[iters];
    double myStrCatResults[iters];
    FILE *outFile = fopen("PerfTest.csv", "w");
    for (int i = 0; i < iters; i++)
    {
        n <<= 1;
        iterResults[i] = n;
        strCatResults[i] = runStrCatTest(n);
        myStrCatResults[i] = runMyStrCatTest(n);
        printf("Completed iteration: %d\n", i);
        printf("\tNumber concatenations: %d\n", n);
        printf("\tstrcat: %f\n", strCatResults[i]);
        printf("\tmyStrCat: %f\n", myStrCatResults[i]);
    }
    fprintf(outFile, "Number of concatenations,strcat Results,mod strcat Results\n");
    for (int i = 0; i < iters; i++)
    {
        fprintf(outFile, "%d,%f,%f\n", iterResults[i], strCatResults[i], myStrCatResults[i]);
    }

    return 0;
}