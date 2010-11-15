/*
 * Mathew Duhon
 *
 * lab 4
 * mypwd.c
 *
 */

#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 2048

void lookParent(struct stat *parent_st, char *pathName[], int *index);

int main () {
    struct dirent *curr_dir;
    struct stat  curr_st;
    DIR * dircurr;
    int index, i;
    char temp[PATH_MAX + 100], * pathName [PATH_MAX/2];
    dircurr = opendir(".");
    index = 0;
    temp[0] = '/';
    if((curr_dir = readdir(dircurr))) {
        stat(curr_dir->d_name, &curr_st);
    } 

    closedir(dircurr);
    lookParent(&curr_st, pathName, &index);

    for(i = 1; i <= index; i++){
        strcat(temp, pathName[index-i]); 
        if(strlen(temp) > PATH_MAX) {
            perror("path too long");
            exit(3);
        }
        temp[strlen(temp)] = '/';    
    }
    temp[strlen(temp)-1] = '\n';    
    printf("%s", temp);
    return 0;
}

void lookParent(struct stat *parent_st, char *pathName[], int *index) {
    DIR * dircurr;
    struct dirent *curr_dir;
    struct stat curr_st;
    struct stat toPass_st;
    chdir("..");
    dircurr = opendir(".");
    if((curr_dir = readdir(dircurr))) {
        stat(curr_dir->d_name, &toPass_st);
    }
    while((curr_dir = readdir(dircurr))) {
        if((curr_dir->d_name[0] == '.') && isalpha(curr_dir->d_name[1])) {
                continue;
        }
            stat(curr_dir->d_name, &curr_st);
        if(parent_st->st_ino == curr_st.st_ino && parent_st->st_dev ==
                curr_st.st_dev) {
            pathName[*index] = malloc(sizeof(curr_dir->d_name));
            strcpy(pathName[*index], curr_dir->d_name);
            *index = *index +1;
            closedir(dircurr);
            lookParent(&toPass_st, pathName, index);
        }
    }
}
