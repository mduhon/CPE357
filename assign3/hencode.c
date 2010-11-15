/*
 * Mathew Duhon
 *
 * hencode
 *
 */

#include "htable.h"

void  arrangeCharArr(node *sortedArr[], node *newArr[], int  elem);
void  printTable(node *arr[], int elem, int outFile);
int  encode(unsigned char *buf, int len, int outFile, node *arr[]);  


int main(int argc, char *argv[]) {

unsigned char *buf;
int inFile, num, elem, outFile;
node *head;
node *arr[charMax];
node *indexArr[charMax];

    head = NULL;
    elem = 0;
    buf = malloc(RW_MAX * sizeof(unsigned char));
    if(!buf) {
        perror("malloc");
        exit(4);
    }
    if( argc < 2 ) {
        printf("Usage: inFile [outFile]\n");
        exit(1);
    }
    else { 
        if((inFile = open(argv[1],  O_RDONLY, S_IRUSR )) < 0) {
            perror("can't open inFile");
            exit(2);
        }
        
        if(argc == 3) {
            if((outFile = open(argv[2],  O_WRONLY | O_TRUNC | O_CREAT,
                               S_IRUSR | S_IWUSR )) < 0) {
                perror("can't open outFile");
                exit(2);
            }
        }else if(argc == 2) {
            outFile = STDOUT_FILENO;
        }
        while((num=read(inFile, buf, RW_MAX)) > 0) {
            head = addChars(head, buf, num, &elem);
        }
        
        if(!head) {
            if((write(outFile, &num, sizeof(int))) < 0) {
                 perror("write");
                exit(3);
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
            if(elem > charMax)
                elem = charMax;
            makeTable(head, arr);
            arrSort(arr, elem);
            head = createTree(head);
            traverseTree(head);
            arrangeCharArr(arr, indexArr,  elem);

/* prints the table to the start of the file */
            if(head) {
                printTable(arr, elem, outFile);
                lseek(inFile, 0, 0);
                while((num=read(inFile, buf, RW_MAX)) > 0) {
                    encode(buf, num, outFile, indexArr);  
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
        }
    }
    for(num = 0; num < elem; num++) {
        free(arr[num]);
    }
    free(buf);
    return 0; 
}
 
/*
 * takes in the arr of sorted pointers to the nodes
 * and prints them to the file
 */
void  printTable(node *arr[], int elem, int outFile) {
int i;
    if((write(outFile, &elem, sizeof(int))) < 0) {
        perror("write");
        exit(3);
    }   
    for(i = 0; i<elem; i++) {
        if((write(outFile, &arr[i]->c, sizeof(char))) < 0) {
            perror("write");
            exit(3);
        }
        if((write(outFile, &arr[i]->freq, sizeof(int))) < 0) {
            perror("write");
            exit(3);
        }    
    }
}
            

/* 
 * makes a second array to store the pointers to the nodes
 * based upon their character index for quick acccess when
 * writting the path to the file
 */
void  arrangeCharArr(node *sortedArr[], node *newArr[], int elem) {
    int i;
    for(i = 0; i < elem; i++) {
        newArr[sortedArr[i]->c] = sortedArr[i];
    }
    return;
}

/*
 * takes the input read and then stores the path for each letter
 * and then puts it in the byte till it is full and then writes that
 * to the file
 */
int  encode(unsigned char *buf, int len, int outFile, node *arr[]) {

static unsigned char bits;
static int index;
int i, j, pLen;
    bits = 0;
    index = 7;

    for(i = 0; i<len; i++) {
        pLen = strlen(arr[buf[i]]->path);
        for(j = 0; j < pLen; j++ ) {
            if(index == -1) {
                index = 7; 
                if((write(outFile, &bits, sizeof(char))) < 0) {
                    perror("write");
                    exit(3);
                 }
                bits = 0;
            }
            if( arr[buf[i]]->path[j] == '1') {
              bits = bits | (1 << index);
            }
             index--;
            }   
    }
    if(index != 7) {
        if((write(outFile, &bits, sizeof(char))) < 0) {
            perror("write");
            exit(3);
        }
    }
    return 0;
}  


