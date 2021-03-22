#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//4a
// provide signle argument on the command line

double usersupplied; 	//Value for user to enter
double xppo; 		   //x to positive odd power
int neg_one = -1; 	  //negative 1
int podd = 1;        //positive odd number
double n_factorial = 1.0;  //n factorial
double two_n = 2.0;  // 2 to the power n
double two_n_n = 1.0;
double pow_exp_integrand; // value of power serires expansion of the integrand @ 0
double pow_exp_integrand_n;
double cum_stan_norm;




int main(int argc, char *argv[]){
	
	sscanf(argv[1], "%lf", &usersupplied);
	
	if(isnan(usersupplied) || isinf(usersupplied)){
		printf("Error in user supplied value\n");
	}
	
	
	xppo = usersupplied;
	
	pow_exp_integrand = (xppo * neg_one) / ((double) pow(two_n, 0) * podd * n_factorial); //formula top of page 79
	
	printf("x to an odd power: %lf\n is negative?: %d\n", xppo, neg_one);
	printf("power series expansion of integrand for n = zero: %lf\n", pow_exp_integrand);
	
	for(int n = 1; n < 10; n++){
		
		xppo = xppo * pow(usersupplied, 2);
		neg_one = neg_one * -1;
		podd = podd + 2;
		n_factorial = n_factorial * (double) n;
		two_n_n = two_n_n * 2;
		
		pow_exp_integrand_n = pow_exp_integrand + ((xppo * neg_one)/(two_n_n * podd * n_factorial));
	}
	
	cum_stan_norm = pow_exp_integrand_n / (0.5 + sqrt(2.0 * 3.14159265359));
	
	printf("Answer: %lf\n", cum_stan_norm);
		
	
	return EXIT_SUCCESS;
	
	
}