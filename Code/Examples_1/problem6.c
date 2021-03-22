#include <stdio.h>


int main() 
{
    float const a = 1.175494123456789e-38;
    double const b = 1.175494123456789e-38;	

    printf("print float: %.15e \n", a);
    printf("print double: %.15e \n", b);
    printf("The number is forced to be stored as float type\nSince only 23 bits are used for the significand, float can exactly represent up to six decimal digits after the floating-point\n");
    
    return 0;
}
