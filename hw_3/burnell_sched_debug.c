/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 18 March 2024
*    Purpose: Learn about schedulers by implementing a priority
*             scheduling non pre-emptive algorithm
*           build priority queue by sorting the processes
*               by their priority (0 being highest priority)
*           Given: fcfs.c example as a starting point
*           Input: burst time and priority of each process
*           Output: print burst time, waiting time, and turnaround time
*  Note: Selection Sort help taken from: https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/  
*  Note Compile and run with> gcc burnell_scheduler.c -o sched && ./sched
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void swap(int* xp, int* yp);
void selectionSort(int *burst, int*priority, int*pname, int n);
void printArray(int* arr, int size);

int main()
{
    //pt is the priority 
    //pname is for tracking process names and order
    int i, n, *bt, *wt, *tat, *pt, *pname;
    float avgtat, avgwt;
    //num processes is 3
    n = 3;

    bt = (int*)malloc(n*sizeof(int));
    wt = (int*)malloc(n*sizeof(int));
    tat = (int*)malloc(n*sizeof(int));
    pname = (int*)malloc(n*sizeof(int));
    pt = (int*)malloc(n*sizeof(int));

    //burst time for each process
    bt[0]=2;
    bt[1]=3;
    bt[2]=4;

    //priority for each process
    pt[0]=4;
    pt[1]=0;
    pt[2]=3;

    // fill the process names array to sort later
    for(int i=0; i<n; i++) {
        pname[i] = i;
    }

    // sort the processes by priority to build the queue
    selectionSort(bt,pt,pname,n);

    // calculate their metrics and "run" the processes
    // note: wt and tat built in execution order
    int curr_process = 0; // zero here is placeholder
    int prev_process = 0; //zero here is placeholder
    wt[0] = 0;
    tat[0] = bt[0];
    printf("bt P1: %d\n", bt[0]);

    for(i=1; i<n; i++)
    {
        curr_process = pname[i];
        prev_process = pname[i-1];
        wt[i] = wt[i-1] + bt[i-1];  //waiting time[p] = waiting time[p-1] + Burst Time[p-1]
        tat[i] = wt[i] + bt[i];     //Turnaround Time = Waiting Time + Burst Time
        printf("curr_process: %d\n", curr_process);
        printf("prev_process: %d\n", prev_process);
        printf("wt[prev_process]: %d\n", wt[i-1]);
        printf("bt[prev_process]: %d\n", bt[i-1]);
        printf("wt[curr_process]: %d\n", wt[i]);
    }

    printf("pname: ");
    printArray(pname, n);

    printf("burst time: ");
    printArray(bt, n);

    printf("wait time: ");
    printArray(wt, n);



    // for(i=0; i<n; i++)
    // {
    //     avgwt += wt[i];
    //     avgtat += tat[i]; 
    // }
    // avgwt = avgwt/n;
    // avgtat = avgtat/n;

    // printf("\n PROCESS \t PRIORITY \t BURST TIME \t WAITING TIME \t TURNAROUND TIME \n");
    // printf("------------------------------------------------------------------------\n");
    // for(i=0; i<n; i++)
    // {
    //     printf(" P%d \t\t %d \t\t %d \t\t %d \t\t %d \n", i, pt[i],bt[i], wt[i], tat[i]);
    // }

    // printf("\n Average Waiting Time = %f \n Average Turnaround Time = %f \n", avgwt, avgtat);

    // printf("\n GAANT CHART \n");
    // printf("---------------\n");
    // //print the processes in the order they are executed (print the pname array
    // //  with correct wait times and turn around times for each process)
    // curr_process = 0;
    // for(i=0; i<n; i++)
    // {
    //     curr_process = pname[i];
    //     printf(" %d\t|| P%d ||\t%d\n", wt[curr_process], curr_process, tat[curr_process]);
    // }
    return 0;
}

void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

// Function to perform Selection Sort 
// input: the burst array and the priority array
void selectionSort(int* burst, int*priority, int*pname, int len) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of 
    // unsorted subarray 
    for (i = 0; i < len - 1; i++) { 
        // Find the minimum element in 
        // unsorted array 
        min_idx = i; 
        for (j = i + 1; j < len; j++) 
            if (priority[j] < priority[min_idx]) 
                min_idx = j; 
  
        // Swap the found minimum element 
        // with the first element
        swap(&priority[min_idx], &priority[i]);
        swap(&burst[min_idx], &burst[i]);
        swap(&pname[min_idx],&pname[i]); 
    } 
} 

// Function to print an array 
void printArray(int* arr, int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
