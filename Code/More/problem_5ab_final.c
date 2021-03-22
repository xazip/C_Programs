#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int argc, char *argv[]){
	
	int n;
	int mx;
	double alpha;
	double beta;
					//Define user entry values
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &mx);
	sscanf(argv[3], "%lf", &alpha);
	sscanf(argv[4], "%lf", &beta);
					// read in specified values
					
	
	double p[mx];
	double q[mx];
	double n_factorial[mx];
	
	p[0] = 1;
	q[0] = 1;
	n_factorial[0] = 1;
	
	//define p in terms of alpha and beta => replace mu with (a/b) based on gamma distribution
	
	for(int i = 1; i < mx; i++){
		
		p[i] = p[i - 1] * (n * alpha + i - 1) / beta;
		
	}
	
	for(int i = 1; i < mx; i++){
		n_factorial[i] = n_factorial[i-1] * i; //factorial expansion
	}
	
	for(int i = 1; i < mx; i++){
		
		p[i] /= n_factorial[i]; 
		printf("p is: %lf\n", p[i]);
		
	}
	
	for(int i = 1; i < mx; i++){
		for(int j = 0; j < i; j++){
			
			q[i] += ((n*(i-j)-j) * (p[i-j] * q[j])) / (i * p[0]);
			printf("q is: %lf\n", q[i]);
		}
	}
	
}