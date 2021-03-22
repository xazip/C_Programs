#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void compute_q(double *ps, double *qs, int count, int n);

int main(int argc, char *argv[])
{
    int mm, n;
    double alpha, beta;

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &mm);
    sscanf(argv[3], "%lf", &alpha);
    sscanf(argv[4], "%lf", &beta);

    mm += 1;

    double ps[mm];
    double qs[mm];
    double n_fac[mm];

    n_fac[0] = 1;
    for(int i = 1; i < mm; i++){
        n_fac[i] = n_fac[i-1] * i;
        // printf("nfac: %lf\n", n_fac[i]);
    }

    ps[0] = 1;

    for (int i = 1; i < mm; i++) {
        ps[i] = ps[i-1] * (alpha + i - 1) / beta; // compute the moment
        // printf("the %dth moment of x: %lf\n", i, ps[i]);
    }

    for (int i = 0; i < mm; i++) {
        ps[i] /= n_fac[i]; // obtain the correct ps
        // printf("the ps: %lf\n", ps[i]);
    }

    compute_q(ps, qs, mm, n); // compute qs

    for (int i = 1; i < mm; i++) {
        qs[i] *= n_fac[i]; // obtain the moment
        printf("moment - %d: %lf\n", i, qs[i]);
    }

    // compute the correct momnet
    // for (int i = 1; i < mm; i++) {
    //     ps[i] = ps[i-1] * (n*alpha + i - 1) / beta; // compute the moment
    // }
    // printf("the %dth moment of the sum is: %lf\n", mm-1, qs[mm-1]);

    return 0;
}

void compute_q(double *ps, double *qs, int count, int n)
{
    qs[0] = 1.0;

    for(int i = 1; i < count; i++){
        double tmp_sum = 0;
        
        for (int j = 0; j < i; j++) {
            tmp_sum += (n * (i - j) - j) * ps[i-j] * qs[j];
        }
        
        qs[i] = tmp_sum / i;
    }

}
