#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef union {
  unsigned int ui;
  float f;
 } u;

int main(void) {
    float rr[] = {NAN, INFINITY, -INFINITY, INFINITY+1};
    const char *outp[4];
    outp[0] = "NAN";
    outp[1] = "INFINITY";
    outp[2] = "-INFINITY";
    outp[3] = "INFINITY + 1";

    u myu;

    for (int j = 0; j < 4; j++) {
        myu.f = rr[j];

        unsigned int mask_start = 1u << 31;
        printf("the binary representation of %s:\n", outp[j]);

        for(int i = 0; i < 32; i++, mask_start >>= 1) {
            printf("%d", (myu.ui & mask_start) >> (31 - i));
            if(((i+1)%8) == 0) printf(" ");
        }

        printf("\n");
    }

    return 0;
}
