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

void parse(char * args[], char sign[]);
void printStages(stage * head);
stage * makeStages(stage * head, char *args[], char sign[]);

int main (int argc, char * argv[]) {
    stage * head;
    char *args[TEN];
    char sign[TEN];

    head = NULL;
    fprintf(stdout,"line: ");
    parse(args, sign);
    head = makeStages(head, args, sign);
    printStages(head);
    return 0;
}



void parse(char * args[], char sign[]) {
    char *line, *tok;
    char **buf;
    int x = 0, y = 0;

    line = malloc(sizeof(char)*MAX_LINE);
    if(!line) {
        perror("malloc");
        exit(1);
    }

    fgets(line, MAX_LINE, stdin);
    buf = &line;
    args[x++] = line;tok = line;
    for(x = 0;y<strlen(line); y++) {
        if(line[y] == '|' || line[y] == '<' || 
                line[y] == '>') {
            sign[x++] = line[y];
        }
    }
    
    x = 0;
    while((tok = strsep(buf, "<>|"))) {
        args[x++] = tok;
    }
    args[x+1] = '\0';
/*        if(head == NULL) {
            head = malloc(sizeof(*head));
               
            if(!head) {
                perror("malloc");
                exit(1);
            }
            head->argv[0] = temp;
            head->numStage = 0;
            head->stagenext = NULL;
            if(sign[x] != '<') {
                head->input == "original stdin"
            }
            if(sign[x] != '>') {
                head->output == "original stdout"
            }
        }*/

}

stage * makeStages(stage * head, char *args[], char sign[]){
    int x, y, curStage;
    stage * new, * old;
    char in[14] = "original stdin";
    char out[15] = "original stdout";
    char stage[16] = "pipe to stage ";

    x = curStage = 0;
    if(!sign[x]) {

        head = malloc(sizeof(*head));
        if(!head) {
            perror("malloc");
            exit(1);
        }
        head->numStage = curStage++;
        head->argc = 1;
        strcpy(head->line, args[0]);
        head->line[strlen(head->line)-1] = '\0';
        head->next = NULL;
        strcpy(head->input,in);
        strcpy(head->output,out);
        strcpy(head->line, args[0]);
        head->argv[0] = args[1];

    }
    while(sign[x]){
        if(head == NULL) {
            head = malloc(sizeof(*head));
               
            if(!head) {
                perror("malloc");
                exit(1);
            }
            for(y = 0; args[y]; y++) {
                head->argv[y] = args[y+1];
            }
            head->numStage = curStage++;
            head->argc = y;
            strcpy(head->line, args[0]);
            head->line[strlen(head->line)] = '\0';
            strcpy(head->line, args[0]);
            strcpy(head->line, args[0]);
            head->next = NULL;
            if(sign[x] == '<') {
                strcpy(head->input, args[1]);
            } else {
                strcpy(head->input,in);
            }
            if(sign[x] == '>') {
                strcpy(head->output, args[1]);
            } else if(sign[x] == '|') {
                strcpy(head->output, stage);
                head->output[15] = '1';
            } else { 
                strcpy(head->output,out);
            }
            new = head;
        } else {
            old = new;
            new = malloc(sizeof(*head));
            if(!new) {
                perror("malloc");
                exit(1);
            }
            new->numStage = curStage++;
            new->argc = 1;
            strcpy(new->line, args[curStage]);
            new->line[strlen(new->line)] = '\0';
            new->next = NULL;
            old->next = new;

            if(sign[x] == '<') {
                strcpy(new->input, args[1]);
            } else {
                strcpy(new->input,in);
            }
            if(sign[x] == '>') {
                strcpy(new->output, args[1]);
            } else if(sign[x] == '|') {
                strcpy(new->output, stage);
                new->output[15] = '1';
            } else { 
                strcpy(new->output,out);
            }

        }
        x++;
    }

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

}

