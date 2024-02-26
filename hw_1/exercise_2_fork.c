/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 25 February 2024
*    Purpose: Explore Processes parents and children by creating and 
*             calling a parent process that prints goodbye and a child
*             that prints hello
*
*  Note Compile and run with> gcc exercise_2_fork.c -o hello_fork && ./hello_fork
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("start (pid:%d)\n", (int) getpid());
    
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello pid:(%d)\n", (int) getpid());

    } else {
        // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
