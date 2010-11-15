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

#define RW_MAX 4096
#define charMax 255

typedef struct Node{
	unsigned char c;
	int freq;
	char path [charMax];
	struct Node *left, *right, *next, *prev;
} node;




void makeTable(node *head, node * arr[]);
void printTree(node * head [], int elem);
void traverseTree(node *headm);
void arrSort(node *arr[], int len);
void stackUpLefts(node * toAdd, node *stack[], int *top, char *path,
	   	int *index, char side);
void lookLeft(node *head, char path[], char side, int index);
int hasNext(int top);
node * insertA(node *head, unsigned char  c, int *elem, int freq);
node * sort(node *head, node *toAdd);
node * addChars(node *head, unsigned char *buf, int num, int *elem);
node * createTree(node *head);



