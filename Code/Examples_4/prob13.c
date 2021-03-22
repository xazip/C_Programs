#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <string.h>



//should run as ./newton -a a -e eps -0 ini


double func(double x, double a){
	return x*x - a;
}

double func_derivative(double x){
	return (double) 2.0 * x;
}


void Newton_Method(double x, double eps, double a){
	
	
	double fx = func(x, a) / func_derivative(x);
	
	while(fabs(fx) >= eps){
		
		fx = func(x, a) / func_derivative(x);
		
		x = x - fx;
		
	}
	
	printf("The value is : %0.15lf\n", x);
	
}

int main(int argc, char *argv[]){
	
	// give default values 
	double a = 2.0;
	double eps = 0.0001;
	double ini = 1.0;
	// char str_a[4];
	// char str_e[4];
	// char str_ini[4];

	int i = 1;	/* argv[0] is the executable name */
	while (i < argc) {

		switch (argv[i][1]) {		/* assume -f style flags */
		case 'a':
			if (++i < argc)
				if(!sscanf(argv[i], "%lf", &a)) {
					fprintf(stderr, "[ERROR] Could not read command line for -a!\n");
					return EXIT_FAILURE;
				}
			break;
		case 'e':
			if (++i < argc)
				if(!sscanf(argv[i], "%lf", &eps)) {
					fprintf(stderr, "[ERROR] Could not read command line for -e!\n");
					return EXIT_FAILURE;
				}
			break;
		case '0':
			if (++i < argc)
				if(!sscanf(argv[i], "%lf", &ini)) {
					fprintf(stderr, "[ERROR] Could not read command line for -0!\n");
					return EXIT_FAILURE;
				}
			break;
		default:
			fprintf(stderr, "%s [-a <double> -e <double> -0 <double>]\n"
				"\t-a <double>\ta to find the square root\n"
				"\t-e <double>\teps for tolerance\n"
				"\t-0 <double>\tthe starting value\n",
							argv[0]);
			exit(EXIT_FAILURE);
		}
		++i;
	}


	// //double fx;
	// sscanf(argv[1], "%s", str_a);
	
	// if (strcmp(str_a, "-a") == 0) {
    //     sscanf(argv[2], "%lf", &a);
    // } else {
    //     printf("-a is not provided\n");
    //     return 0;
    // }
	// sscanf(argv[3], "%s", str_e);
	
    // if (strcmp(str_e, "-e") == 0) {
    //     sscanf(argv[4], "%lf", &eps);
    // } else {
    //     printf("-e is not provided\n");
    //     return 0;
    // }
	// sscanf(argv[5], "%s", str_ini);
	
    // if (strcmp(str_ini, "-0") == 0) {
    //     sscanf(argv[6], "%lf", &ini);
    // } else {
    //     printf("-0 is not provided\n");
    //     return 0;
    // }

	if(a == 0) {
		printf("The value is : %0.15lf\n", 0.0);
		return 0;
	} else if (a < 0) {
		printf("making a a positive value\n");
		a = -a;
	}

	double x;
	if (ini < 0) {
		printf("making %lf to %lf\n", ini, -ini);
		x = -ini;
	} else {
		x = ini;
	}
	
	if(x == 0){
		
		x = 0.00001;
		
	}
	
	Newton_Method(x, eps, a);
	
	
	
	
	return 0;
	
	
	
}

