#include <string.h>
#include <dirent.h>
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
    char pad[12];
    long size;
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
DIR * dircurr;
struct dirent *curr_dir;
struct stat curr_st;
int outFile, inFile;
    if(argc < 3) {
        perror("Usage");
        exit(1);
    }
    if((inFile = open(argv[2], O_RDONLY, S_IRUSR | S_IWUSR)) < 0) {
        perror("bad inFile");
        exit(1);
    }

    dircurr = opendir(".");
    curr_dir = readdir(dircurr);
    while((head = readHeader(inFile))) {
        if(!head->size)
            continue;
        head->name[strlen(head->name)] = '5';
        if((outFile = open(head->name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
            perror("open");
            exit(3);
        }


        copyInfo(((head->size/512)+1), inFile, outFile);
        close(outFile);
        free(head);
    }
/*    head = readHeader(inFile);
    head->name[strlen(head->name)] = '5';
    if((outFile = open(head->name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
        perror("open");
        exit(3);
    }


    copyInfo(((head->size/512)+1), inFile, outFile);
    close(outFile);
    free(head);

    head = readHeader(inFile);
    head->name[strlen(head->name)] = '5';
    if((outFile = open(head->name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
        perror("open");
        exit(3);
    }


    copyInfo(((head->size/512)+1), inFile, outFile);

    free(head);*/
    close(inFile);
    close(outFile);

    return 0;
}
header *readHeader(int inFile) {
    header * head;
    head = malloc(sizeof(header));
    if(!head) {
        perror("readHeader");
        exit(3);
    }
    read(inFile, head->name, sizeof(head->name));
    read(inFile, head->mode, sizeof(head->mode));
    read(inFile, head->uid, sizeof(head->uid));
    read(inFile, head->gid, sizeof(head->gid));
    read(inFile, head->pad, sizeof(head->pad));
    head->size = strtol(head->pad,NULL, 8);
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
    read(inFile, head->pad, sizeof(head->pad));

    return head;
}




int copyInfo(int size, int from, int to) {
    int x, y;
    unsigned char block[512];

    for(x=0; x<size; x++) {
        y = 0;
        read(from, block, sizeof(block));
        while(y<512) {
            if(block[y] > 0) {
                dprintf(to,"%c",block[y]);
            }
            y++;
        }
    }
    return 0;
} 
