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
    }

    child = fork();
    if(child == 0) {
        child = getpid();
        if(excelp(argv[1], NULL)  == -1) {
            perror("exec: ");
        }
    } else { 
        if(child == -1) {
            perror("fork");
            exit(1);
        }
    }
    if(!waitpid(child, &status, WNOHANG)) {

    }


    return child;
}
