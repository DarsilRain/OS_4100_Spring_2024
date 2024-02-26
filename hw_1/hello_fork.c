/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 25 February 2024
*    Purpose: Explore Processes parents and children by creating and 
*             calling a parent process that prints goodbye and a child
*             that prints hello
* 
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("hello (pid:%d)\n", (int) getpid());
    //int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (main)
        printf("parent of %d (pid:%d)\n",
        rc, (int) getpid());
    }
    return 0;
}
