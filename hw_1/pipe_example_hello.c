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

    switch (child1 = fork()) {
        case -1:
            // error - abort
            break;
        case 0:   /* child 1 */
            close(pipefds[0]);
            write(pipefds[1], "Hello, brother!", 15);
            exit(0);
        default:  /* parent */
            // nothing
    }

    switch (child2 = fork()) {
        case -1:
            // error - abort
            break;
        case 0:   /* child 2 */
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
        default:  /* parent */
            // nothing
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