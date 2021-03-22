#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_ITER 40
#define PII 3.14159265358979323846

int main(int argc, char *argv[])
{
    double x, x_n, x2, result, cn = 1.0;
    int n = 0, odd = 1;

    sscanf(argv[1], "%lf", &x);

    x_n = x;
    x2 = x * x;

    result = cn * x_n;

    for (n = 1; n < NUM_ITER; n++) {
        odd += 2;
        cn /= odd;
        // cn *= 1.0/odd;
        x_n *= x2;

        // printf("odd: %d, cn: %lf, x_n: %lf\n", odd, cn, x_n);
        
        result += cn * x_n;
        // printf("the summand: %lf, result: %lf\n", cn * x_n, result);
    }

    result = result / exp(x2 / 2.0) / sqrt(2.0 * PII) + 0.5;

    printf("Phi of %lf is %.15lf\n", x, result);

    return 0;
}
