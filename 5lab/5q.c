#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * mystrstr(char *haystack, char *needle);

int main () {
char * word;
    word =  mystrstr("racecar", "car");
    if (word)
        printf("%s\n",word); 
    word =  mystrstr("racecar", "");
    if (word)
        printf("%s\n", word); 
    word =  mystrstr("superlongwordwithac", "car");
    if (word)
        printf("%s\n", word); 
    word =  mystrstr("racecarcar", "car");
    if (word)
        printf("%s\n", word); 
    return 0;
}

char  * mystrstr(char *haystack, char *needle){
    int i, j, hLen, nLen, index;
    int found;
    char * start;
    char * occ = NULL;
    if(haystack == NULL || needle == NULL ) {
        return occ;
    }
    found = index = 0;
    hLen = strlen(haystack);
    nLen = strlen(needle);

    for(i = 0; i< hLen; i++) {
        if(haystack[i] == needle[0]) {
            found = 1;
            start = &haystack[i];
            for( j =1; j<nLen && index < hLen; j++) {
                index = i + j;
                if(haystack[index] != needle[j]) {
                    found = 0;
                    break;
                }
            }
        }
            if(found ) {
                occ = malloc(nLen);
                memcpy(occ, start, nLen);
                break;
            }
    }
    return occ;
}
