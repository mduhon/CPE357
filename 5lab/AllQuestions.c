#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nonce(x) x-x
#define div(x,y) (x/y)

struct node_st {
    int data;
    struct node_st *next;
};

struct node_st *sorted_insert_list(int num, struct node_st *list);
char * mystrstr(char *haystack, char *needle);
int twice (int x);

int main () {
   char * word;
    int x =2; 
    int y =3;
    int A = 2;
    int B = 3;
    char *cp = "abcdef";
    int grade[6] = {4, 3, 2, 1, 0, -1};


   printf("%d\n", &grade[3] - &grade[2]);
/* This is because the size of an int is 4 and when you subtract
 * it it is 4 bytes away which is 1
 * */ 
 
 printf("%d\n", strlen((char*)(&grade[3])));
/* This answer depends upon if the machine is a big endian or
 * little endian mahcine. 
 */
 
 
 
    printf("%f\n", div(1, 2.0));
/* This is 0.5 because of the 2.0 being a floating number not an
 * integer since it has the '.o' at the end. This changes it to 
 * a  floating point division
 */
 
  printf("%d\n", div(twice(nonce(y)), nonce(twice(x))));
/* If you expand this out it would look like:
 * div(twice(x-x),nonce(x+x) then
 * twice(y-y)/twice(x) - twice(x)
 */
    
    
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
        
        
    struct node_st * test;
    test = NULL;
    test = sorted_insert_list(5, test);
    test = sorted_insert_list(8, test);
    test = sorted_insert_list(3, test);
    test = sorted_insert_list(1, test);
    test = sorted_insert_list(6, test);
    test = sorted_insert_list(0, test);

    while(test->next) {
        printf("Num is %d\n", test->data);
        test = test->next;
    }
    return 0;
}
struct node_st *sorted_insert_list(int num, struct node_st *list) {
    struct node_st *new, *head;

    new = malloc(sizeof(*new));
    if(!new) {
        perror("new node");
        exit(17);
    }
    if(!list){ 
        new->data = num;
        new->next = NULL;
        return new;
    }  else {
        head = list;

/*base case, if it is to go at the start of the list
 */        
        if( num < list->data) {
            new->data=num;
            new->next=list;
            head = new;
            return head;
        }

/* changed my code around from the test to make it more robust 
 * and make it more readable, has less ifs and else ifs
 */        
        while(list != NULL) {
            if( list->next != NULL) {
                if((num > list->data && num < list->next->data) ||
                         list->data == num) {
                    new->data = num;
                    new->next = list->next;
                    list->next = new;
                    return head;
                } else {
                   list = list->next; 
                }  
            } else {
                    new->data = num;
                    new->next = NULL;
                    list->next = new;
                    return head;
            }
        }
    }


return head;
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

int twice (int x) {
 return x + x;
}


