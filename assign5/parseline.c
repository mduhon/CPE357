#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 512

typedef struct {
    char * input;
    char * output;
    int argc;
    char * argv;
    int numStage;
    struct stage * next;


} stage;

void parse(stage * head);
void printStages(stage * head);

int main (int argc, char * argv[]) {
    stage  head;

    fprintf(stdout,"line: ");
    parse(&head);
    printStages(&head);
    return 0;
}



void parse(stage * head) {
    char *line, *tok;
    char sign[50];
    char temp[MAX_LINE];
    char **buf;
    int x = 0, y = 0;

    line = temp;
/*    line = malloc(sizeof(char)*MAX_LINE);
    if(!line) {
        perror("malloc");
        exit(1);
    }*/

    fgets(line, MAX_LINE, stdin);
    buf = &line;
    tok = line;
    for(;y<512; y++) {
        if(line[y] == '|' || line[y] == '<' || 
                line[y] == '>') {
            sign[x++] = line[y];
        }
    }
    sign[x+1] = '\0';
/*    while(x < strlen(line)) {
        if(*tok == '|' || *tok == '<' ||
                *tok == '>' || isspace(*tok)) {
            temp = malloc(x-y);
            if(!line) {
                perror("malloc");
                exit(1);
            }
            strncpy(temp, tok, x-y);
            printf("found: %s\n", temp);
            y = x+1;
        }
        tok++;
        x++;
    }*/
    x = 0;
    while((tok = strsep(buf, "<>|"))) {
        printf("tok = %s\t", tok);
        if(x<strlen(sign)){
            printf("followed by %c\n",sign[x++]);
        }else 
            printf("end\n");
    }

}


void printStages(stage * head) {

}

