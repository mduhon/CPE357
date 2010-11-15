#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


int main () {

    struct dirent *curr_dir;
    struct stat  curr_st;
    struct stat parent_st;
    struct stat grand_st;
    DIR * dircurr;
    int index;
    char * temp, * pathName [PATH_MAX];
    dircurr = opendir(".");
    index = 0;
    if((curr_dir = readdir(dircurr))) {
        stat(curr_dir->d_name, &curr_st);
    } 
    temp = malloc(sizeof(curr_dir->d_name));
    strcpy(temp, curr_dir->d_name);
    closedir(dircurr);
    
    chdir("..");
    dircurr = opendir(".");
    while((curr_dir = readdir(dircurr))) {
            stat(curr_dir->d_name, &parent_st);
        if(parent_st.st_ino == curr_st.st_ino && parent_st.st_dev ==
                curr_st.st_dev) {
            printf("%s/%s\n", curr_dir->d_name,temp);
            printf("%d\n", (int)curr_st.st_ino);
            printf("%d\n", (int)curr_st.st_dev);
            printf("%d\n", (int)parent_st.st_ino);
            printf("%d\n", (int)parent_st.st_dev);
            break;
        }
    }
    free(temp);
    temp = malloc(sizeof(curr_dir->d_name));
    strcpy(temp, curr_dir->d_name);
    closedir(dircurr);
    
    chdir("..");
    dircurr = opendir(".");
    while((curr_dir = readdir(dircurr))) {
            stat(curr_dir->d_name, &grand_st);
        if(parent_st.st_ino == grand_st.st_ino && parent_st.st_dev ==
                grand_st.st_dev) {
            printf("%s/%s\n", curr_dir->d_name,temp);
            printf("%d\n", (int)grand_st.st_ino);
            printf("%d\n", (int)grand_st.st_dev);
            printf("%d\n", (int)parent_st.st_ino);
            printf("%d\n", (int)parent_st.st_dev);
            break;
        }
    }
   return 0;
}
