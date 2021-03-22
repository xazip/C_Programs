#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    printf("Sizeof(char): %zu\n", sizeof(char));
    printf("Sizeof(signed char): %zu\n", sizeof(signed char));
    printf("Sizeof(short): %zu\n", sizeof(short));
    printf("Sizeof(int): %zu\n", sizeof(int));
    printf("Sizeof(long): %zu\n", sizeof(long));
    printf("Sizeof(unsigned short): %zu\n", sizeof(unsigned short));
    printf("Sizeof(unsigned int): %zu\n", sizeof(unsigned int));
    printf("Sizeof(unsigned long): %zu\n", sizeof(unsigned long));
    printf("Sizeof(float): %zu\n", sizeof(float));
    printf("Sizeof(double): %zu\n", sizeof(double));
    printf("Sizeof(long double): %zu\n", sizeof(long double));
    return 0;
}
