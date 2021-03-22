#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double usersupplied; 	//Value for user to enter
double xppo; 		   //x to positive odd power
int podd = 1;
double cn = 1.0;
double two_n;
int n = 0;

double gx;
double answer;

int main(int argc, char *argv[]){
	
	sscanf(argv[1], "%lf", &usersupplied);
	
	if(isnan(usersupplied) || isinf(usersupplied)){
		fprintf(stderr,"Error in user supplied value, user entered: %lf\n", usersupplied);
	}
	
	xppo = usersupplied;
	two_n = (double) pow(usersupplied, 2);
	
	gx = cn*xppo;
	
	for(n = 1; n < 10; n++){
		podd = podd + 2;
		cn = cn * (1.0 / podd);
		xppo = xppo * two_n;
		
		gx = gx + ((cn * gx) + 1.0);
		
	}
	
	answer = 0.5 + ((double) (1.0/(sqrt(2 * 3.14159265359))) * gx;
	
	
	return 0;
}