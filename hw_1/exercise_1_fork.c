/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 25 February 2024
*    Purpose: Explore Processes parents and children by creating and 
*             calling a parent process that prints goodbye and a child
*             that prints hello
*
*  Note Compile and run with> gcc exercise_1_fork.c -o hello_fork && ./hello_fork
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("start (pid:%d)\n", (int) getpid());
    int x = 100;
    
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello pid:(%d)\n", (int) getpid());
        printf("child value of x: %d \n",x);
        x = x+1;
        printf("child x+1=%d \n", x);
    } else {
        // parent goes down this path (main)
        printf("goodbye (pid:%d)\n", (int) getpid());
        printf("parent value of x: %d \n",x);
        x = x+1;
        printf("parent x+1=%d \n", x);
    }
    return 0;
}
