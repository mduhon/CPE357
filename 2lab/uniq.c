/*
 * Mathew Duhon
 * CPE357
 * lab 2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * read_long_line (FILE *file);

int main(){
	char * cur_line, * prev_line=NULL;
	int cmp;
/* This will read input from stdin till EOF
 * It also prints out the current line if it is
 * different than the previous line
 */	
	while((cur_line = read_long_line (stdin)) != NULL){
		if(prev_line){
			if((cmp = strcmp(cur_line, prev_line)!=0))
				printf("%s\n",cur_line);
		}else 
			printf("%s\n",cur_line);
		if(prev_line!=NULL)
			free(prev_line);
		prev_line = cur_line;
		

	}
/*  Frees everything that is currently in use
 */	
	if(cur_line!=NULL)
		free(cur_line);	
	if(prev_line!=NULL)
		free(prev_line);
	return 0;
}

/* This reads in a line until a 
 * '\n' is found then returns 
 * the line that is found.
 * It also tests for errors
 * when mallocing for data
 */
char *read_long_line (FILE *file){
	static int size =10;
	int i=0;
	char * line = malloc(size);
	if(line==NULL){
		perror("Not enough Mem: ");
		exit(1);
	}
	while(((line[i] = getchar())!= EOF)) {
		if( i == size-1) {
			size *=2;
			line = realloc(line, size);
			if(line==NULL){
				perror("Not enough mem: ");
				exit(1);
			}
		}
		line[i+1] = '\0';
		if(line[i] == '\n')
			return line;
		i++;
	}
	if(line[i] == EOF)
		return NULL;	
	return line;
}
