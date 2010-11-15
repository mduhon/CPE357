#include <string.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    long size2;
    char mtime[12];
    char chksum [8];
    char typeflag;
    char linkname [100];
    char magic [6];
    char version [2];
    char uname [32];
    char gname [32];
    char devmajor [8];
    char devminor [8];
    char prefix [155];
} header;

header *readHeader(int inFile);
int copyInfo(int size, int from, int to);


int main (int argc, char * argv[]) {
header *head;
int outFile, inFile;
    if(argc != 2) {
        perror("Usage");
        exit(1);
    }
    if((inFile = open(argv[1], O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
        perror("bad inFile");
        exit(1);
    }
    head = readHeader( inFile);
    head->name[strlen(head->name)] = '1';
    if((outFile = open(head->name, O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
        perror("open");
        exit(3);
    }

    fprintf(stdout,"the size is %ld\n", head->size2);
    if((write(outFile, &head->size2, sizeof(long)) < 0)) {
            perror("write");
            exit(3);
    }
    write(STDOUT_FILENO, &head->size2, sizeof(long int));

    return 0;
}
header *readHeader(int inFile) {
    header * head;
    head = malloc(sizeof(*head));
    if(!head) {
        perror("readHeader");
        exit(3);
    }
    read(inFile, head->name, sizeof(head->name));
    read(inFile, head->mode, sizeof(head->mode));
    read(inFile, head->uid, sizeof(head->uid));
    read(inFile, head->size, sizeof(head->size));
    read(inFile, head->mtime, sizeof(head->mtime));
    read(inFile, head->chksum, sizeof(head->chksum));
    read(inFile, &head->typeflag, sizeof(head->typeflag));
    read(inFile, head->linkname, sizeof(head->linkname));
    read(inFile, head->magic, sizeof(head->magic));
    read(inFile, head->version, sizeof(head->version));
    read(inFile, head->uname, sizeof(head->uname));
    read(inFile, head->gname, sizeof(head->gname));
    read(inFile, head->devmajor, sizeof(head->devmajor));
    read(inFile, head->devminor, sizeof(head->devminor));
    read(inFile, head->prefix, sizeof(head->prefix));
    head->size2 = strtol(head->size,NULL, 8);
/*    write(STDOUT_FILENO, head->name, strlen(head->name));
    write(STDOUT_FILENO, head->mode, strlen(head->mode));
    write(STDOUT_FILENO, head->uid, strlen(head->uid));*/

    return head;
}




int copyInfo(int size, int from, int to) {

    return 0;
} 
