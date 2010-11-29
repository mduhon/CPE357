#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
pid_t child, parent;
int status;

    printf("Hello, World!\n");
    parent = getpid();

    printf("This is  the parent, pid %d\n", parent);

    child = fork();
    if(child == 0) {
        child = getpid();
        printf("This the child, pid %d\n", child);
    } else { 
        if(child == -1) {
            perror("fork");
            exit(1);
        }
    }
    if(!waitpid(child, &status, WNOHANG)) {
        printf("This is  the parent, pid %d, siging off.\n", parent);
    }


    return 0;
}
