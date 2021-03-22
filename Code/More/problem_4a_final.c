#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define M_PI acos(-1.0)
#define NUM_ITER 40

int main(int argc, char *argv[]){
	
	double user_supplied;
	double xp_odd;
	double two_p_n = 1.0;
	double n_factorial;
	double pow_exp_integrand;
	double cum_stan_norm;
	int neg_one = 1; //for n = 0
	int podd = 1;
	n_factorial = 1;
	
	sscanf(argv[1], "%lf", &user_supplied);
	
	if(isnan(user_supplied) || isinf(user_supplied)){
		fprintf(stderr, "Error in user supplied value, user entered: %lf\n", user_supplied);
	}
	
	
	
	pow_exp_integrand = user_supplied; //n = 0 case
	
	xp_odd = user_supplied;
	
	for(int n = 1; n < NUM_ITER; n++){
		neg_one *= -1;
		podd = ((2*n) + 1);
		n_factorial *= (double) n;
		two_p_n = (double) pow(2, n);
		xp_odd *= pow(user_supplied, 2);
		
		pow_exp_integrand += ((xp_odd * neg_one) / (two_p_n * podd * n_factorial));
	}
	
	cum_stan_norm = pow_exp_integrand / (0.5 + sqrt(2.0 * M_PI));
	
	printf("User entered %lf, therefore Phi is: %.15lf\n", user_supplied, cum_stan_norm);
	
	return 0;w
	
	
	
}