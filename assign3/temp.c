#include <stdio.h>
#include <stdlib.h>


int main () {
int i, j, byte;
int temp;
unsigned char g = 94;
i =0;
	byte = 7;
	for(; i< 8; i++) {
		if(byte == -1) {
			byte = 7;
		}else if (g & (1<<byte)) {
			printf("goes right\n");
			byte--;
		}
		else {
			byte--;
			printf("goes left\n");
		}
	}
return 0;
}
