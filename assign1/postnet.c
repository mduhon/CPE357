/* Mathew Duhon
** cpe357 assignment 1
** postnet 
*/



#include <stdio.h>
#include <ctype.h>
void printBar(int input [12], int length);
int main () {
	int i=0;
	int input[12];
	char trash [20];

/*checks for new line to print the bar and checks for input that is too long
 * if its a letter, space or digit and either adds it to the input or 
 * ignores it */
	while((input[i]=getc(stdin))!=EOF){ 
		if(input[i]=='\n'){
			printBar(input, i);
			i=0;
		}
		else if(i>12){	
			printf("i is >11\n");		
			scanf("%s", trash);
			i=0;
		}
		else if(isalpha(input[i])){
			printf("Invalid delivery data\n");
			scanf("%s", trash);
			i=0;
		}
		else if(isspace(input[i]));
/*subtracts 48 to convert from the char number to the actual number on the
 * ascii table*/			
		else if (isdigit(input[i])){
			input[i]=input[i]-48;
			i++;
		}
				
	}
return 0;
}


/* prints the bar and the input. It starts wtih printing the input one by one
 * then calculates the check sum and adds it to the input then displays 
 * the postnet code*/
void printBar(int input [12], int length){
	int j, sum=0, check=0;
	if(length==0)
		return;
	for(j=0; j<=11; j++){
		if(j<length){
			printf("%d", input[j]);
			sum+=input[j];
		}
		else
			printf(" ");
	}
	while(sum%10!=0){
		check++;
		sum++;
	}
	input[length +1]=check;
	printf("-> :");
	for(j=0; j!=length+2; j++){
		switch (input[j]){
			case 0:
			   printf("::..."); 
			   break;
			case 1:
			   printf("...::");
			   break;
			case 2:
			   printf("..:.:");
			   break;
			case 3:
			   printf("..::.");
			   break;
			case 4:
			   printf(".:..:");
			   break;
			case 5:
			   printf(".:.:.");
			   break;
			case 6:
			   printf(".::..");
			   break;
			case 7:
			   printf(":...:");
			   break;
			case 8:
			   printf(":..:.");
	        	   break;
			case 9:
			   printf(":.:..");
			   break;
		}
	}
	
printf(":\n");
return;
}

