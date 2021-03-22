/**
 * KSD Comments
 * - LKCS: using spaces not tabs
 * - check argc before accessing argv[1], as this can cause segfault
 * - if it doesn't segfault, x may be used uninitialized if scanf fails
 * - advanced (not expected)
 *   * check sscanf success and handle it if fails
 * - 10 operations (best I've seen is 6)
 * - good work; it works
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_ITER 40
#define PII 3.14159265358979323846

int main(int argc, char *argv[])
{
	double x, x_n, x2, result, two_n = 1.0, n_fac = 1.0, n = 0;
	int odd = 1, neg = 1;

	/* [KSD] using short circuit to avoid accessing argv[1]
	 * [KSD] check return value on sscanf; 0 means failed to read double
	 */
	if (argc < 2 || !sscanf(argv[1], "%lf", &x)) {
		fprintf(stderr, "[ERROR] Could not read command line!\n");
		return EXIT_FAILURE;
	} /*replaced code: sscanf(argv[1], "%lf", &x);*/

	x_n = x;
	x2 = x * x;

	result = x_n * neg / (two_n * odd * n_fac);

	for (n = 1; n < NUM_ITER; n++) {
		neg *= -1;
		odd += 2;
		n_fac *= n;
		two_n *= 2;
		x_n *= x2;

		// printf("neg: %d, odd: %d, n_fac: %e, two_n: %lf, x: %e\n", neg, odd, n_fac, two_n, x_n);

		result += x_n * neg / (two_n * odd * n_fac);
		// printf("step %d - result is: %lf; summand is %lf\n", n, result, x_n * neg / (two_n * odd * n_fac));
	}

	result = result / sqrt(2.0 * PII) + 0.5;

	printf("Phi of %lf is %.15lf\n", x, result);

	return EXIT_SUCCESS;	/* [KSD] use macro in stdlib.h */
}
