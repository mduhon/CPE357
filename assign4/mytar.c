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

header *readHeader();

int main () {
header *head;
int file;

    head = readHeader();
    head->name[strlen(head->name)] = '1';
    if(!(file = open(head->name, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO))) {
        perror("open");
        exit(3);
    }

    write(file, head->size, strlen(head->size));

    return 0;
}
header *readHeader() {
    header * head;
    head = malloc(sizeof(*head));
    if(!head) {
        perror("readHeader");
        exit(3);
    }
    read(STDIN_FILENO, head->name, sizeof(head->name));
    read(STDIN_FILENO, head->mode, sizeof(head->mode));
    read(STDIN_FILENO, head->uid, sizeof(head->uid));
    read(STDIN_FILENO, head->size, sizeof(head->size));
    read(STDIN_FILENO, head->mtime, sizeof(head->mtime));
    read(STDIN_FILENO, head->chksum, sizeof(head->chksum));
    read(STDIN_FILENO, &head->typeflag, sizeof(head->typeflag));
    read(STDIN_FILENO, head->linkname, sizeof(head->linkname));
    read(STDIN_FILENO, head->magic, sizeof(head->magic));
    read(STDIN_FILENO, head->version, sizeof(head->version));
    read(STDIN_FILENO, head->uname, sizeof(head->uname));
    read(STDIN_FILENO, head->gname, sizeof(head->gname));
    read(STDIN_FILENO, head->devmajor, sizeof(head->devmajor));
    read(STDIN_FILENO, head->devminor, sizeof(head->devminor));
    read(STDIN_FILENO, head->prefix, sizeof(head->prefix));
/*    write(STDOUT_FILENO, head->name, strlen(head->name));
    write(STDOUT_FILENO, head->mode, strlen(head->mode));
    write(STDOUT_FILENO, head->uid, strlen(head->uid));*/

    return head;
}
