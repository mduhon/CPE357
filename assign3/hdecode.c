/* 
 * Mathew Duhon
 *
 * Hdecode.c
 *
 */

#include "htable.h"


void decode(int outFile, unsigned char *buf, int num, int *printed,
       int totalFreq, node * head);

int main ( int argc, char * argv[]) {

unsigned char *buf, newChar;
int inFile, num, elem, num_chars, i, freq, outFile, printed;
int totalFreq;
node *head;
node *arr[RW_MAX];

    head = NULL;
    elem = printed = totalFreq = 0;
    buf = malloc(RW_MAX * sizeof(unsigned char));
    if(!buf) {
        perror("malloc");
        exit(4);
    }
    if( argc < 1 ) {
        printf("Usage: [(ininFile | -) [outinFile]]\n");
        exit(1);
    }
    else if(argc == 2 || argc == 3){
        if((inFile = open(argv[1],  O_RDONLY, S_IRUSR )) < 0) {
            perror("can't open inFile");
            exit(2);
        }
        if((num = read(inFile, &num_chars, sizeof(int))) > 0);
        if(num_chars == 0) {
            if(argc == 3) {
                if((outFile = open(argv[2],  O_WRONLY | O_TRUNC | O_CREAT,
                               S_IRUSR | S_IWUSR )) < 0) {
                    perror("can't open outFile");
                    exit(2);
                }
                close(inFile);
                close(outFile);
            }
            return 0;
        }
/*reads in the table in the start of the file*/
        for(i = 0; i < num_chars; i++) {
                if((num=read(inFile, &newChar, sizeof(char))) > 0) {
                    if((num=read(inFile, &freq, sizeof(int))) > 0) {
                        head = insertA(head, newChar, &elem, freq); 
                        totalFreq += freq;
                    }
                } 
                if(num == 0 && !head)
                    return 0;
        }
        makeTable(head, arr);
        arrSort(arr, elem);
        head = createTree(head);
        traverseTree(head);
        if(argc == 3) {
            if((outFile = open(argv[2],  O_WRONLY | O_TRUNC | O_CREAT,
                               S_IRUSR | S_IWUSR )) < 0) {
                perror("can't open outFile");
                exit(2);
            }
        }else if(argc == 2) {
            outFile = STDOUT_FILENO;
        }
        if(num_chars == 1) {
            for(i=0; i < head->freq; i++) 
                if((write(outFile, &head->c, sizeof(char))) < 0) {
                    perror("write");
                    exit(3);
                }
            
        } else {
            while((num=read(inFile, buf, RW_MAX)) > 0) {
                decode(outFile, buf, num, &printed, totalFreq, head);
            }
        }
        if(close(inFile)){
            perror("close");
            exit(47);
        }
        if(close(outFile)){
            perror("close");
            exit(47);
        }
    }else {
        printf("Usage: [(ininFile | -) [outinFile]]\n");
        exit(1);
    }
    for(i = 0; i < elem; i++) {
        free(arr[i]);
    }
    free(buf);
    return 0; 
}

/*
 * this takes the buf read into the file 
 * then decodes it using the table that was previously made
 * and it prints it to the outfile based upon the path 
 * made in traverseTree
 */
void decode(int outFile, unsigned char *buf, int num, int *printed,
       int totalFreq, node * head){
    int byte, index;
    node *trav;
    trav = head;
    byte = 7;
    index = 0;
    while(trav && index < num) {
        if(byte == -1) {
            byte = 7;
            index++;
        }
        if(!trav->left && !trav->right) {
            if((write(outFile, &trav->c, sizeof(char))) < 0) {
                perror("write");
                exit(3);
            }
            *printed = *printed +1;
            if(*printed == totalFreq)
                return;
            trav = head;
        }else if (buf[index] & (1<<byte)) {
            trav = trav->right;
            byte--; }
        else {
            trav = trav->left;
            byte--;
        }
    }
}    
