/* Mathew Duhon
 * assign 6
 * mush
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parseline.h"
#include <fcntl.h>

/* define read and write ends
 */
#define READ_END 0
#define WRITE_END 1
extern char **environ;

int main (int argc, char * argv[]) {
pid_t children[5];
sigset_t mask;
int status,child, x, p, stageCount;
int fileIn, fileOut;
char in[] = "original stdin";
char out[] = "original stdout";
int pipes[10][2];
stage * temp;
stage * head = NULL;

    while(1) {
        p = stageCount = 0;

        fprintf(stdout, "8-P ");
        fflush(stdout);
        head = parse(head, &stageCount);
        if(stageCount > 10) {
            fprintf(stderr,"Pipeline too deep\n");
        }
        for(x = 0; x < stageCount; x++) {
            if(pipe(pipes[x])) {
                fprintf(stderr,"Pipe %d\n", x);
            }
        }
        x = 0;
        while(head) {
            if((sigemptyset(&mask) == -1) ||
                    (sigaddset(&mask, SIGINT) == -1)) {
                perror("Sig block");
                exit(-1);
            }    
            children[x] = fork();
            if(children[x] == 0) {
                if(stageCount == 1) {
                    if(execvp(head->argv[0],head->argv)  == -1) {
                        perror("exec");
                    }
                    exit(0);
                }
                if(x == 0) {
                    if(strcmp(head->input,in) != 0) {
                        fileIn = open(head->input, O_RDONLY);
                        if(-1 == dup2(pipes[0][WRITE_END], fileIn)) {
                            perror("dup2:0");
                            exit(-1);
                        }
                    } else {
                        if(-1 == dup2(pipes[0][WRITE_END], STDOUT_FILENO)) {
                            perror("dup2:0");
                            exit(-1);
                        }
                    }
                    for(p=0; p<stageCount; p++) {
                        close(pipes[p][READ_END]);
                        close(pipes[p][WRITE_END]);
                    }

                }
                if(x ==  stageCount-1) {
                    if(strcmp(head->output,out) != 0) {
                        fileOut = open(head->input, O_WRONLY);
                        if(-1 == dup2(pipes[x-1][WRITE_END], fileOut)) {
                            perror("dup2:0");
                            exit(-1);
                        }
                    } else {
                        if(-1 == dup2(pipes[x-1][READ_END], STDIN_FILENO)) {
                            perror("dup2:2");
                            exit(-1);
                        }
                    }
                    for(p=0; p<stageCount; p++) {
                        close(pipes[p][READ_END]);
                        close(pipes[p][WRITE_END]);
                    }

                } 
                if (x > 0 && x < stageCount-1){
                    if(-1 == dup2(pipes[x-1][READ_END], STDIN_FILENO)) {
                        perror("dup2:1");
                        exit(-1);
                    }
                    if(-1 == dup2(pipes[x][WRITE_END], STDOUT_FILENO)) {
                        perror("dup2:1.1");
                        exit(-1);
                    }
                    for(p=0; p<stageCount; p++) {
                        close(pipes[p][READ_END]);
                        close(pipes[p][WRITE_END]);
                    }
                }
            
                    if((sigemptyset(&mask) == -1) ||
                            (sigdelset(&mask, SIGINT) == -1)) {
                        perror("Sig block");
                        exit(-1);
                    }
                    if(execvp(head->argv[0],head->argv)  == -1) {
                        perror("exec");
                    }
                exit(-1); 
            } else { 
                if(children[x] == -1) {
                    perror("fork");
                    exit(1);
                }
                /* clean up */
            }
            temp = head;
            head = head->next;
            free(temp);
            x++;
        }
        for(p=0; p<stageCount; p++) {
            close(pipes[p][READ_END]);
            close(pipes[p][WRITE_END]);
        }

        for(;x>0;x--) {
            child = wait(&status);
            if(child != -1) {
                x++;
            }
        }
    }

    return 0;
}
