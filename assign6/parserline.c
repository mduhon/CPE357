#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 512
#define TEN 10

typedef struct Stage{
    char line[MAX_LINE];
    char input[50];
    char output[50];
    int argc;
    char * argv[TEN];
    int numStage;
    struct Stage * next;


} stage;

stage * parse(stage * head);
void printStages(stage * head);
stage * makeStages(stage * head, char * line);

int main (int argc, char * argv[]) {
    stage * head;

    head = NULL;
    fprintf(stdout,"line: ");
    head = parse(head);
    printStages(head);
    return 0;
}


stage * parse(stage * head) {
    char *line, *tok;
    char **buf;

    line = malloc(sizeof(char)*MAX_LINE);
    if(!line) {
        perror("malloc");
        exit(1);
    }

    fgets(line, MAX_LINE, stdin);
    buf = &line;
    tok = line;
    
    while((tok = strsep(buf, "|"))) {
        head = makeStages(head, tok);       
    }
   return head; 
}

stage * makeStages(stage * head, char * line){
    stage * last, * trav;
    char *tok, **buf, temp [2];
    char in[] = "original stdin";
    char out[] = "original stdout";
    char stageTo[] = "pipe to stage ";
    char stageFrom[] = "pipe from stage ";
    int x;
    static int to = 0, from = 0;
    static int curStage = 0;

    if(head == NULL) {
        head = malloc(sizeof(*head));
        if(!head) {
            perror("malloc");
            exit(1);
        }
        last = NULL;
        trav = head;
    } else {
        trav = head;
        while(trav->next){
            trav = trav->next;
        }
        last = trav;
        trav = trav->next;
        trav = malloc(sizeof(*trav));

        if(!trav) {
            perror("malloc");
            exit(1);
        }
    }
    
    
    if(line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
    }
    
    if(!last) {
        strcpy(trav->input, in);
    } else {
        strcpy(trav->input, stageFrom);
        sprintf(temp, "%d", curStage-1);
        strcat(trav->input, temp);
        if(last) {
            strcpy(last->output, stageTo);
            sprintf(temp, "%d", curStage); 
            strcat(last->output, temp);
        }

        last->next = trav;
    }
    strcpy(trav->output, out);
    strcpy(trav->line, line);
    buf = &line;
    tok = line;
    x = 0;
    while((tok = strsep(buf, " "))) {
        if(strlen(tok) == 0) {
            continue;
        }
        if(*tok == '>') {
            if(to) {
                if(last) {
                    fprintf(stderr,"%s: ambiguous input\n",trav->argv[0]);
                    exit(1);
                }
                fprintf(stderr,"%s: bad input redirection\n", trav->argv[0]);
                exit(1);
            }
            tok = strsep(buf, " ");
            strcpy(trav->output, tok);
            to = 1;
        } else if(*tok == '<') {
            if(from) {
                if(last) {
                    fprintf(stderr,"%s: ambiguous input\n",trav->argv[0]);
                    exit(1);
                }
                fprintf(stderr,"%s: bad input redirection\n", trav->argv[0]);
                exit(1);
            }
            tok = strsep(buf, " ");
            strcpy(trav->input, tok);
            from = 1;
        } else {
            trav->argv[x++] = tok;
        }
    } 
    if(!trav->argv[0]) {
         fprintf(stderr,"invalid null command\n");
         exit(1);
    }
    trav->numStage = curStage++;
    trav->argc = x;
    trav->next = NULL;
    
    return head;
}



void printStages(stage * head) {
    int x;
    stage * trav = head;
    x = 0;
    while(trav) {
        printf("--------\n");
        printf("Stage %d: \"%s\"\n", trav->numStage, trav->line);
        printf("--------\n");
        printf("\t input: %s\n", trav->input);
        printf("\t output: %s\n", trav->output);
        printf("\t argc: %d\n", trav->argc);
        printf("\t argv: \"%s\"", trav->argv[0]);
        for(x = 1; trav->argv[x]; x++) {
            printf(",\"%s\"", trav->argv[x]);
        }
        trav = trav->next;
        printf("\n");
    }
    printf("\n");

}

