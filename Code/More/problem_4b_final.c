#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_PI acos(-1.0)

int main(int argc, char *argv[]){
	
	double user_supplied;
	double xp_odd;
	//double two_p_n = 1.0;
	double gx;
	double cum_stan_norm;
	double cn = 1.0;
	int podd = 1;
	
	
	sscanf(argv[1], "%lf", &user_supplied);
	
	if(isnan(user_supplied) || isinf(user_supplied)){
		fprintf(stderr, "Error in user supplied value, user entered: %lf\n", user_supplied);
	}
	
	gx = cn * user_supplied; //n = 0 case, c_sub_0 = 1
	
	xp_odd = user_supplied;
	
	for(int n = 1; n < 10; n++){
		
		podd += ((2*n) + 1);
		cn *= pow(podd, -1);
		xp_odd *= pow(user_supplied, 2);
			
		gx += ((cn * xp_odd) + 1.0);
	}
	
	cum_stan_norm = (pow(sqrt(2 * M_PI), -1) * gx) + 0.5;
	
	printf("User entered %lf, therefore Phi is: %.15lf\n", user_supplied, cum_stan_norm);
	
	return 0;
}