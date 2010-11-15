/*
 * Matt Duhon
 * CPE 357
 * Huffman table creator 
 *
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RW_MAX 256

typedef struct Node{
	unsigned char c;
	int freq;
	char path [RW_MAX];
	struct Node *left, *right, *next, *prev;
} node;




void makeTable(node *head, node * arr[]);
void traverseTree(node *head, int elem);
void arrSort(node *arr[], int len);
void stackUpLefts(node * toAdd, node *stack[], int *top, char *path,
	   	int *index, char side);
void lookLeft(node *head, char path[], char side, int index);
int hasNext(int top);
node * insertA(node *head, unsigned char  c, int *elem);
node * sort(node *head, node *toAdd);
node * addChars(node *head, unsigned char *buf, int num, int *elem);
node * createTree(node *head);

void printTree(node * head [], int elem) {
	int i;
	for(i = 0; i <elem; i++) {
		printf("0x%02x: %s\n", head[i]->c, head[i]->path);
	}
	return;
}
int main ( int argc, char * argv[]) {

unsigned char *buf;
int file, num, elem;
node *head;
node *arr[RW_MAX];

	head = NULL;
	elem = 0;
	buf = malloc(RW_MAX);
	if(!buf) {
		perror("malloc");
		exit(4);
	}
	if( argc < 1 ) {
		printf("Usage: <filename>)\n");
		exit(1);
	}
	else {
		if((file = open(argv[1],  O_RDONLY, S_IRUSR )) < 0) {
			perror("can't open file");
			exit(2);
		}
		while((num=read(file, buf, RW_MAX)) > 0) {
		    head = addChars(head, buf, num, &elem);
		}
		if(num == 0 && !head)
				return 0;
		if(close(file)){
			perror("close");
			exit(47);
		}
	}
	makeTable(head, arr);
	arrSort(arr, elem);
	head = createTree(head);

	traverseTree(head, elem);
	printTree(arr, elem);
	free(buf);
	return 0; 
}


node *  addChars(node *head, unsigned char *buf, int num, int *elem ) {
int i;


	for(i = 0; i<num; i++) {
		head = insertA(head, buf[i], elem);
	}
	return head;
}


node * insertA(node *head, unsigned char  c, int *elem) {
int i;
node  *curr, *new;
	if(head == NULL) {
		head = malloc( sizeof(*new));
		if(!head) {
			perror("insertA");
			exit(3);
		}
		head->c = c;
		head->freq = 1;
		head->next = head->left = head->right = head->prev = NULL;
		*elem = *elem+1;
		for(i=0; i<RW_MAX; i++) 
			head->path[i] = '\0';
		return head;
	}
	curr = head;
	while(curr->next) {
		if(head->c == c) {
			head->freq++;
			head = sort(head->next, head);
			return head;
		}
		if(curr->c == c) {
			curr->freq++;
			if(curr->prev) {
				curr->prev->next = curr->next;
			}
			curr->next->prev = curr->prev;
			head = sort(head, curr);
			return head;
		}else {
			curr=curr->next;
		}
	}
	if(head->c == c) {
			head->freq++;
			if(head->next) {
				head = sort(head->next, head);
			}
			return head;
		}
	if(curr->c == c) {
		curr->freq++;
		if(curr->prev) {
			curr->prev->next = curr->next;
		}		
		head = sort(head, curr);
		return head;
	}
	new =  malloc(sizeof(*head));
	if(!new) {
		perror("new entry");
		exit(3);
	}
	new->c = c;
	new->freq = 1;
	new->next = new->prev = NULL;
	new->left = new->right = NULL;
	*elem = *elem+1;
	for(i=0; i<RW_MAX; i++) 
			new->path[i] = '\0';
	head = sort(head, new);
	return head;
}

node * sort(node *head, node *toAdd) {
	node * temp;
	temp = head;

	if(head->freq == toAdd->freq && head->c > toAdd->c) {
		toAdd->next = head;
		head = toAdd;
		toAdd->next->prev = toAdd;
		return head;
	}

	if(head->freq > toAdd->freq) {
		toAdd->next = head;
		head = toAdd;
		toAdd->next->prev = toAdd;
		return head;
	}
	while(temp->next && temp->next->freq < toAdd->freq) {
		temp  = temp->next;
	}
	while(temp->next && temp->next->freq == toAdd->freq && temp->next->c
		   	<  toAdd->c) {
			temp = temp->next;
	}

	toAdd->next = temp->next;
	temp->next = toAdd;
	if(toAdd->next) {
		toAdd->next->prev = toAdd;
	}
	toAdd->prev = temp;
	return head;
}

node * createTree(node *head) {

node  *new;
	while(head->next) {
		new = malloc(sizeof(*head));
		if(!new) {
			perror("createTree");
			exit(2);
		}
			new->freq = head->freq + head->next->freq;
/*			new->c = 0;*/
			new->left = head;
			new->right = head->next;
			if(head->next->next) {
				head =head->next->next;
			} else {
				head = new;
				return head;
			}
			head = sort(head, new);
			head = head;
	}
	return head;
}

void makeTable( node *head, node * arr[]) {
	int i;
	node *trav = head;
	i = 0;
	*arr = calloc(RW_MAX, sizeof(*trav));
	if(!arr) {
		perror("makeTable");
		exit(3);
	}
	while(trav->next && i<RW_MAX) {
		arr[i] = trav;
		trav = trav->next;
		i++;
	}
	arr[i] = trav;
	return;
}

void lookLeft(node *head, char path[], char side, int index) {
	if(head->c >= 0) {
		path[index] = side;
		strncpy(head->path, path, ((index)+1));
	}
	if(head->left) {
		path[index] = side;
		lookLeft(head->left, path, '0', index+1);
	} 
	if(head->right) {
		path[((index)+1)] = '1';
		lookLeft(head->right, path, '1', index+1);
	}
}

void traverseTree(node *head, int elem) {
	int i;
	char path[RW_MAX];
	node * trav = head;
	i = 0;
	if(trav->left){
		lookLeft(trav->left, path, '0', i);
	}
	if(trav->right){
		lookLeft(trav->right, path, '1', i);
	}
	return;
}


void arrSort(node *arr[], int len) {
	node *temp; 
	int i,j;
	for(i = 1; i < len; i++) {
		temp = arr[i];
		j=i;
		while( j != 0 && (arr[j-1]->c > temp->c)) {
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = temp;
	}
}
