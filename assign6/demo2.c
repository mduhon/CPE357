#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1
int main(int argc, char *argv[]) {
int one[2];
int two[2];
pid_t child1, child2, child3;
    if ( pipe(one) ) {
        perror("First pipe");
        exit(1);
    }
    if ( pipe(two) ) {
        perror("Second pipe");
        exit(1);
    } 
    if ( ! (child1 = fork()) ) {
            /* child one stuff*/
            /* dup appropriate pipe ends */
        if ( -1 == dup2(one[WRITE_END],STDOUT_FILENO) ) {
            perror("dup2");
            exit(-1);
        } 
            /* clean up */
        close(one[READ_END]);
        close(one[WRITE_END]);
        close(two[READ_END]);
        close(two[WRITE_END]);
        /* do the exec */
        execl("/bin/ls","ls",NULL);
        perror("/bin/ls");
        exit(-1);
    } 
    if ( ! (child2 = fork()) ) {
            /* child two stuff*/
        if ( -1 == dup2(one[READ_END],STDIN_FILENO) ) {
            perror("dup2");
            exit(-1);
        }
        if ( -1 == dup2(two[WRITE_END],STDOUT_FILENO) ) {
            perror("dup2");
            exit(-1);
        }
            /* clean up */
        close(one[READ_END]);
        close(one[WRITE_END]);
        close(two[READ_END]);
        close(two[WRITE_END]);
        /* do the exec */
        execl("/bin/sort","sort","-r",NULL);
        perror("/bin/sort");
        exit(-1);
   }
    if ( ! (child3 = fork()) ) {
            /* child three stuff */
        if ( -1 == dup2(two[READ_END],STDIN_FILENO) ) {
            perror("dup2");
            exit(-1);
        }
            /* clean up */
        close(one[READ_END]);
        close(one[WRITE_END]);
        close(two[READ_END]);
        close(two[WRITE_END]);
        /* do the exec */
        execl("/bin/more","more",NULL);
        perror("/bin/more");
        exit(-1);
    } 
            /* parent stuff */
            /* clean up */
    close(one[READ_END]);
    close(one[WRITE_END]);
    close(two[READ_END]);
    close(two[WRITE_END]);
    if ( -1 == wait(NULL) ) { /* wait for one child */
        perror("wait");
    }
    if ( -1 == wait(NULL) ) { /* wait for the middle child */
        perror("wait");
    } 
    if ( -1 == wait(NULL) ) { /* wait for the last child */
        perror("wait");
    } 
    exit(0);
    } 
