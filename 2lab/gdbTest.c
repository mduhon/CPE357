#include <stdio.h>
void printStuff();
int addNum(int i);
int main() {
	int i, sum;
       	printf("this is a program to learn gdb\n");
	printStuff();
	for(i=10; i>0; i--)
		sum += addNum(i);
	printf("the sum is %d \n", sum);
return 0;
}

void printStuff() {
	int j=37;
	printf("this just calls a function and prints stuff\n");
	printf("%c %d %x \n", j, j, j);
return;
}

int addNum( int i){
	int sum=0;
	if (i!=0)
		sum+= addNum(i-1);
	return sum;
}
