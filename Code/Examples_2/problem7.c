#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef union {
  unsigned int ui;
  float f;
 } u;

int main(int argc, char *argv[])
{
    char str[4];
    int myi;
    u myu;

    sscanf(argv[1], "%s", str);

    // printf("the second argument is: %s\n", str);

    if(strcmp(str, "-i") == 0) {
        sscanf(argv[2], "%d", &myi);
        printf("integer: %d\n", myi);

        // actual work
        unsigned int mask_start = 1u << 31;
        // printf("this is weird: %u\n", mask_start);

        for(int i = 0; i < 32; i++, mask_start >>= 1) {
            // printf("%d, %u\n", i, mask_start);
            printf("%d", (myi & mask_start) >> (31 - i));
            if(((i+1)%8) == 0) printf(" ");
        }

    } else if (strcmp(str, "-f") == 0) {
        sscanf(argv[2], "%f", &myu.f);
        printf("float: %f\n", myu.f);

        unsigned int mask_start = 1u << 31;

        for(int i = 0; i < 32; i++, mask_start >>= 1) {
            // printf("%d, %u\n", i, mask_start);
            printf("%d", (myu.ui & mask_start) >> (31 - i));
            if(((i+1)%8) == 0) printf(" ");
        }

    } else {
        printf("please input -i for int or -f for float.\n");
    }

    printf("\n");

    return 0;
}

