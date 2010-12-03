#include <sys/wait.h>


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


