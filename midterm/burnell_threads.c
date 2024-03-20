/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 19 March 2024
*    Purpose: Lear about threads
*          a) create five threads
*          b/c) calculate the sum of 1-100 using threads
*               - thread 1 -- sum  1-20
*               - thread 2 -- sum 21-40
*               - thread 3 -- sum 41-60
*               - thread 4 -- sum 61-80
*               - thread 5 -- sum 81-100
*          d) calculate the total sum of all the threads and print
* 
* Referenced https://www.geeksforgeeks.org/multithreading-in-c/ 
* Referenced: http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
* Referenced: https://www.educative.io/answers/how-to-sum-an-array-using-threading-in-c
* Note Compile and run with> gcc burnell_threads.c -o thread && ./thread
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// struct to store input value and output of threads
// begin num, end num, sum
typedef struct data{ int b; int e;}data;

void *sum_function( void *arg )
{
    data* ptr = (data*) arg;
    int start = ptr->b;
    int end = ptr->e;

    //declare sum dynamically
    int *sum = (int*) calloc(1,sizeof(int));
    *sum = 0;

    
    //perform the sum
    for(int i=start; i<=end; i++) {
        *sum += i;
    }
    printf("Passed Arg Start: %d, Passed Arg Stop: %d, Sum: %d\n", start, end, sum);
    pthread_exit(sum);
}

int main()
{
    pthread_t thread1, thread2; //Initialize
    data thread_data[2];
    thread_data[0].b = 0;
    thread_data[0].e = 20;

    thread_data[1].b = 21;
    thread_data[1].e = 40;

    /* Create independent threads each of which will execute function *
    
    */
             
    pthread_create( &thread1, NULL, sum_function, &thread_data[0]);
    pthread_create( &thread2, NULL, sum_function, &thread_data[1]);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    //create space for sum
    int* sum1;
    int* sum2;

    pthread_join( thread1, (void **) &sum1);
    pthread_join( thread2, (void **) &sum2); 

    //print the sums of each part
    printf("Thread 1 returns: %d\n",sum1);
    printf("Thread 2 returns: %d\n",sum2);

    free(sum1);
    free(sum2);
    return 0;
}