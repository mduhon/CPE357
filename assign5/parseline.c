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

void parse(stage * head);
void printStages(stage * head);
stage * makeStages(stage * head, char * line);

int main (int argc, char * argv[]) {
    stage * head;

    head = NULL;
    fprintf(stdout,"line: ");
    parse(head);
    printStages(head);
    return 0;
}


void parse(stage * head) {
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
        makeStages(head, tok);       
    }
    
}

stage * makeStages(stage * head, char * line){
    stage * last, * trav;
    char *tok, **buf;
    char in[] = "original stdin";
    char out[] = "original stdout";
    char stage[] = "pipe to stage ";
    int x;
    static int curStage = 0;

    if(head == NULL) {
        head = malloc(sizeof(*head));
        if(!head) {
            perror("malloc");
            exit(1);
        }
    }
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
    if(line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
    }
    
    if(!last) {
        strcpy(trav->input, in);
    } else {
        strcpy(trav->input, stage);
        strcpy(last->output, stage);
        strcat(trav->input, ((char *) curStage));
        strcat(last->output, ((char *) (curStage+1)));

    }
    strcpy(trav->output, out);
    strcpy(trav->line, line);
    buf = &line;
    tok = line;
    x = 0;
    while((tok = strsep(buf, " "))) {
        if(*tok == '>') {
            tok = strsep(buf, " ");
            strcpy(trav->output, tok);
        } else if(*tok == '<') {
            tok = strsep(buf, " ");
            strcpy(trav->input, tok);
        } else {
            strcpy(trav->argv[x++], tok);
        }
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
        printf("\t argv: \"%s\"", trav->argv[x]);
        for(x = 1; trav->argv[x]; x++) {
            printf(",\"%s\"", trav->argv[x]);
        }
        trav = trav->next;
    }
    printf("\n");

}

