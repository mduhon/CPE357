#include <stdio.h>
#include <stdlib.h>

struct node_st {
    int data;
    struct node_st *next;
};

struct node_st *sorted_insert_list(int num, struct node_st *list);

int main () {

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
