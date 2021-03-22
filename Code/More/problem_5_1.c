#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double ps

int n; 					//number of moments
double alpha;				// shape alpha
double beta;				//rate beta

double n_factorial;

int main(int argc, char *argv[]){
	
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%lf", &alpha);
	sscanf(argv[3], "%lf", &beta);
	
	//recurance, store the number of moments
	
	//gamma for factorial
	
	double n_factorial[nm];
	
	
	for(int i = 1; i < nm; i++){
		
		n_factorial[i] = i * n_factorial[i-1];
		
	}
	
	double p[nm];
	
	for(int i = 1; i < nm; i++){
		
		p[i] = (p[i-1] * ((alpha + (i - 1))/beta)) / n_factorial[i]; //expansion
		
	}
	
	double q[nm]
	
	for(int i = 1; i < nm; i++){
		for(int j = 0; j < i; j++){
			for(int n = 1; n < nm; n++){
				
				q[i] = (q[i] + ((n * (i - j) - j) * p[i-j] * q[j])) / i;
			}
		}
	}
	
	return EXIT_SUCCESS;
}
