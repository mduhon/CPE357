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
void push(node *toAdd, node *stack[], int *top, char side,
	   	char *path, int *index);
void stackUpLefts(node * toAdd, node *stack[], int *top, char *path,
	   	int *index, char side);
int hasNext(int top);
node * next(node *stack[], int *top, int *index, char *path, int top_freq);
node * pop(node *stack[], int *top);
node * insertA(node *head, unsigned char  c, int *elem);
node * sort(node *head, node *toAdd);
node * addChars(node *head, unsigned char *buf, int num, int *elem);
node * createTree(node *head);

void printTree(node * head [], int elem) {
	int i;
	for(i = 0; i <elem; i++) {
		printf("%02x: %s\n", head[i]->c, head[i]->path);
	}
/*	while(head->next) {
		printf("%02x: %s\n", head->c, head->path);
		head = head->next;
	}
		printf("%02x: %s\n", head->c, head->path);*/
/*	if(head) {
		printf("letter is %c  %02x and freq is %d\n", head->c, head->c,
			   	head->freq);
		if(head->left) {
			printf("\thas left node\n");
			printTree(head->left);
		}
		if(head->right) {
			printf("\t\t\thas right node\n");
			printTree(head->right);
		}	
	}*/
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
			printf("%s\n", buf);
		    head = addChars(head, buf, num, &elem);
		}
		if(close(file)){
			perror("close");
			exit(47);
		}
	}
	makeTable(head, arr);
	head = createTree(head);

	traverseTree(head, elem);
	printTree(arr, elem);
	/*while(head) {
		printf("the Letter is %c: freq is %d", head->c, head->freq);
		printf(" the value is %x\n", head->c);
		head=head->next;
	}*/
	/*printTree(head);*/
	free(buf);
	return 0; 
}


node *  addChars(node *head, unsigned char *buf, int num, int *elem ) {
int i;


	for(i = 0; i<num; i++) {
		head = insertA(head, buf[i], elem);
/*		printf("iteration %d\n", i);
		printTree(head);*/
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
		/*	if(curr == head) {
				head = curr->next;
				head = sort(curr, curr);
				return head;
			}*/
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
			new->c = 0;
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

void traverseTree(node *head, int elem) {
	int i, top, top_freq;
	char path[RW_MAX];
	node *stack[RW_MAX];		
	node * trav = head;
	top = elem;
	i = -1;
	top = RW_MAX;
	push(trav, stack, &top, '2', path, &i);
	i = 0;
	top_freq = head->freq;
	if(trav->left) {
		stackUpLefts(trav->left, stack, &top, path, &i, '0');
		i++;
	}
	while(hasNext(top)){
		next(stack, &top, &i, path, top_freq);
	}
	return;
}


void push(node *toAdd, node *stack[], int *top, char side,
	   	char *path, int *index) {
	if(*index >= 0 &&  *index < 256)
	path[*index] = side;
	*top = *top - 1;
	stack[*top] = toAdd;
	return;
}

node * pop(node *stack[], int *top) {
	node * temp = stack[*top];
	*top = *top+1;
	return temp;
}

int hasNext(int top) {
	if( top == RW_MAX) 
		return 0;
	else
		return 1;
}

/*
 * this is the next for traversing the tree in inorder
 */
node * next(node *stack[], int *top, int *index, char *path, int top_freq) {
	node *temp = pop(stack, top);
	if(temp->c > 0) {
		strncpy(temp->path, path, *index);
	}else if(*index > 0 ) {
		*index = *index - 1;
	}
	if(top_freq == temp->freq) {
		path[0] = '1';
		*index = *index-1;
	}
	
	if(temp->right) {
			stackUpLefts(temp->right, stack, top, path, index, '1');
			*index = *index +1;
	}

	return temp;
}

void stackUpLefts(node * toAdd, node *stack[], int *top, char *path,
	   	int *index, char side) {
	push(toAdd, stack, top, side, path, index);
	if(toAdd->left) {
		*index = *index +1;
		stackUpLefts(toAdd->left, stack, top, path, index, '0'); 
	}
	return;
}
