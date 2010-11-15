#include <stdio.h>

#define nonce(x) x-x
#define div(x,y) (x/y)

int twice (int x);

int main () {
    int x =2; 
    int y =3;

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
return 0;
}


int twice (int x) {
 return x + x;
}
