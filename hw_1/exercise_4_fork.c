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
ALso Note: took help from these sites
            https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
            https://stackoverflow.com/questions/13801175/classic-c-using-pipes-in-execvp-function-stdin-and-stdout-redirection
            https://www.rozmichelle.com/pipes-forks-dups/
            https://riptutorial.com/posix/example/26063/connecting-two-child-processes-via-a-pipe
Bash Syntax of my example> cat files.txt | grep fork
******************************************************************************/
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
ALso Note: took help from these sites
            https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
            https://stackoverflow.com/questions/13801175/classic-c-using-pipes-in-execvp-function-stdin-and-stdout-redirection
            https://www.rozmichelle.com/pipes-forks-dups/
            https://riptutorial.com/posix/example/26063/connecting-two-child-processes-via-a-pipe
Bash Syntax of my example> cat files.txt | grep fork
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pipefds[2];
    pid_t child1, child2;

    if (pipe(pipefds)) {
        // error - abort ...
    }

    child1 = fork();

    if(child1 < 0) {
        //fork failed
        fprintf(stderr, "fork failed\n");
    } else if(child1 == 0) {
        close(pipefds[0]);
        write(pipefds[1], "Hello, brother!", 15);
        exit(0);
    }

    child2 = fork();

    if(child2<0) {
        //fork failed
        fprintf(stderr, "fork failed\n");
    } else if(child2 == 0) {
        char buffer[256];
            ssize_t nread;

            close(pipefds[1]);
            nread = read(pipefds[0], buffer, sizeof(buffer) - 1);
            if (nread < 0) {
                // handle error
            } else {
                buffer[nread] = '\0';
                printf("My brother told me '%s'\n", buffer);
            }
            exit(0);
    }

    // Only the parent reaches this point
    close(pipefds[0]);
    close(pipefds[1]);
    if (child1 >= 0) {
        wait(NULL);
        if (child2 >= 0) {
            wait(NULL);
        }
    }
}