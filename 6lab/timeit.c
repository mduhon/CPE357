#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>


void timer (int signum);

int main (int argc, char * argv []) {
    int time, sec, i;
    char *check;
    char end [14] = "Time's up!\n\a";
    struct sigaction sa;
    struct itimerval clock;
    sa.sa_flags = 0;
    sa.sa_handler = timer;
    sigemptyset(&sa.sa_mask);
    sec = 0;

    if(argc != 2) {
        perror("usage : timeit <seconds>");
        exit(1);
    }
    
    check = argv[1];
    for( i =0; i< strlen(check); i++) {
        if(isalpha(check[i])) {
            fprintf(stderr, "usage : timeit <seconds>");
            exit(1);
        }
    }

    if(!sscanf(argv[1], "%d", &time)) {
        perror("sscanf");
        exit(1);
    }
    if(-1 == sigaction(SIGALRM, &sa, NULL)) {
        perror("sigaction");
        exit(2);
    }
    clock.it_interval.tv_sec =  0;
    clock.it_interval.tv_usec = 500000;
    clock.it_value.tv_sec =  0;
    clock.it_value.tv_usec = 500000;
    if(-1 == setitimer(ITIMER_REAL, &clock, NULL)){
        perror("setitimer");
        exit(3);
    }
    for(;;sec++) {
        if(sec == time * 2 ) { 
            printf("\a");
            write(STDOUT_FILENO, end, strlen(end));
            exit(1);
        }
        sigsuspend(&sa.sa_mask);

    }

    return 0;
}

void timer (int signum) {
    static int num = 0;
    char tick [8] = "Tick...";
    char tock [6] = "Tock\n";
    if(++num%2) 
        write(STDOUT_FILENO, tick, strlen(tick));
    else {
        write(STDOUT_FILENO, tock, strlen(tock));
    }
    
}
