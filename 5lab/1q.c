#include <stdio.h>
#include <string.h>

int main () {

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
    return 0;
}
