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
double pow_exp_integrand; // value of power serires expansion of the integrand




int main(int argc, char *argv[]){
	
	sscanf(argv[1], "%lf", &usersupplied);
	
	if(isnan(usersupplied) || isinf(usersupplied)){
		printf("Error in user supplied value\n");
	}
	
	
	xppo = usersupplied;
	
	pow_exp_integrand = (xppo * neg_one) / ((double) pow(two_n, 0) * podd * n_factorial); //formula top of page 79
	
	printf("x to an odd power: %lf\n is negative?: %d\n", xppo, neg_one);
	printf("power series expansion of integrand for n = zero: %lf\n", pow_exp_integrand);
	
	return EXIT_SUCCESS;
	
	
}

