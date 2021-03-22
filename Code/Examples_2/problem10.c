#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int verify_seed(int);
double as183(int[]);
#define length 400
char output_array[length];
double tmp;

int main(void)
{
	int seeds[3] = {2457493, 24927, -8593};	/*< initial seeds */
	int i;

	if (INT_MAX < 5212632) {
		printf("[ERROR] constraints of algorithm unsatisfied!\n");
		exit(EXIT_FAILURE);
	}

	seeds[0] = verify_seed(seeds[0]);
	seeds[1] = verify_seed(seeds[1]);
	seeds[2] = verify_seed(seeds[2]);

	for (i=0; i<length; i++) {

		tmp = as183(seeds);
		// printf("%lf ", tmp);
		output_array[i] = floor(-10*log10(tmp)+0.5);
		printf("%c", output_array[i]);
		// printf("%d;", output_array[i]);

		seeds[0] = verify_seed(rand());
		seeds[1] = verify_seed(rand());
		seeds[2] = verify_seed(rand());

		// printf("\n");
		// printf("%f\n", as183(seeds));
	}
	
	// printf("populated array: %s\n", output_array);
	
	size_t array_length = sizeof(output_array);
	printf("\nlength of array: %lu\n", array_length);

	return(EXIT_SUCCESS);
}

/**
 * We get this function from 2021/flow/randoms.c
 * 
 * Generate pseudo standard uniform random deviate.
 *
 * @param arg_seeds[] three seeds in interval [1,30000]
 * @return pseudo random deviate
 */
double as183(int arg_seeds[])
{
	double unidev;

	arg_seeds[0] = (171*arg_seeds[0]) % 30269;
	arg_seeds[1] = (172*arg_seeds[1]) % 30307;
	arg_seeds[2] = (170*arg_seeds[2]) % 30323;
	
	unidev = arg_seeds[0]/30269.0 + arg_seeds[1]/30307.0 + arg_seeds[2]/30323.0;

	return(unidev - (int) unidev);
} /* as183 */

/**
 * Choose integer in range [1,30000].
 *
 * @param x integer to check
 * @return integer in range [1,30000]
 */
int verify_seed(int x)
{
	x = abs(x) % 30000;
	return(++x);
} /* verify_seed */
