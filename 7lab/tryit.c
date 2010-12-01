#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char * argv[]) {
pid_t child;
int status;

    if(argc != 2) {
        printf("Usage: tryit command\n");
        exit(1);
    }

    child = fork();
    if(child == 0) {
        child = getpid();
        if(execl(argv[1],argv[1], NULL)  == -1) {
            perror("exec");
        }
    } else { 
        if(child == -1) {
            perror("fork");
            exit(1);
        }
    child = wait(&status);
    if(status) {
        printf("Process %d exited with an error value.\n", child);
    } else {
        printf("Process %d succeeded\n", child);
    }
    }
    



    return child;
}
