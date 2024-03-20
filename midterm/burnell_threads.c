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
    // debug statement
    //printf("Passed Arg Start: %d, Passed Arg Stop: %d, Sum: %d\n", start, end, *sum);
    pthread_exit(sum);
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4, thread5; //Initialize
    data thread_data[5];
    thread_data[0].b = 0;
    thread_data[0].e = 20;

    thread_data[1].b = 21;
    thread_data[1].e = 40;

    thread_data[2].b = 41;
    thread_data[2].e = 60;

    thread_data[3].b = 61;
    thread_data[3].e = 80;

    thread_data[4].b = 81;
    thread_data[4].e = 100;

    /* Create independent threads each of which will execute function *
    
    */
             
    pthread_create( &thread1, NULL, sum_function, &thread_data[0]);
    pthread_create( &thread2, NULL, sum_function, &thread_data[1]);
    pthread_create( &thread3, NULL, sum_function, &thread_data[2]);
    pthread_create( &thread4, NULL, sum_function, &thread_data[3]);
    pthread_create( &thread5, NULL, sum_function, &thread_data[4]);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    //create space for sum
    int* sum1;
    int* sum2;
    int* sum3;
    int* sum4;
    int* sum5;

    pthread_join( thread1, (void **) &sum1);
    pthread_join( thread2, (void **) &sum2); 
    pthread_join( thread3, (void **) &sum3); 
    pthread_join( thread4, (void **) &sum4); 
    pthread_join( thread5, (void **) &sum5); 

    //print the sums of each part
    printf("Thread 1 returns: %d\n",*sum1);
    printf("Thread 2 returns: %d\n",*sum2);
    printf("Thread 3 returns: %d\n",*sum3);
    printf("Thread 4 returns: %d\n",*sum4);
    printf("Thread 5 returns: %d\n",*sum5);

    printf("Grand Total: %d\n", (*sum1+*sum2+*sum3+*sum4+*sum5));

    free(sum1);
    free(sum2);
    free(sum3);
    free(sum4);
    free(sum5);

    return 0;
}