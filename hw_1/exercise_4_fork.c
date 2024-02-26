/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 25 February 2024
*    Purpose: Explore Processes parents and children by creating and 
*             calling a parent process that prints goodbye and a child
*             that prints hello
*           * put all the knowledge together to understand how it is 
*               useful in the Linux system
*
*  Note Compile and run with> gcc exercise_4_fork.c -o hello_fork && ./hello_fork
ALso Note: took help from this site 
            https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/

Bash Syntax of my example> ls | grep fork
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // create the pipes
    int fd1[2]; // two ends of first pipe
    int fd2[2]; // two ends of second pipe

    char ls_command[] = "ls";
    char grep_command[] = "grep";

    if(pipe(fd1) == -1){
        fprintf(stderr, "pipe one failed\n");
        return 1;
    }

    if(pipe(fd2) == -1){
        fprintf(stderr, "pipe two failed\n");
        return 1;
    }

    int rc = fork();
    if (rc < 0) {
    // fork failed
         fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child path

        //close reading end of first pipe
        close(fd1[0]);

        //read a string using the first pipe
        char grep_arg[100];
        read(fd1[0],grep_arg,100);

        // TODO: do a thing (send output of one to input of the other)
        

    } else {
        // parent goes down this path
        char grep_arg[100];

        //close reading end of first pipe
        close(fd1[0]);

        // write ls command to first pipe, then close
        write(fd1[1], ls_command, strlen(ls_command)+1);
        close(fd1[1]);

        //wait for the child to send the grep command
        wait(NULL);

        //close the writing end of the second pipe
        close(fd2[1]);

        //read string from child
        read(fd2[0], grep_arg, 100);
        
    }
    return 0;
}
