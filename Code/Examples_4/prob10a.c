#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long double comp_w(int *k_array, long double *error, int k);
void set_to_inc_by_one(int*const array, const int index, const int length);
int advance_array(int*const array, const int length, const int max);

int main(int argc, char *argv[]){

  //int n = 30, k = 10;
  int n = 30, k = 10;

  int i = 1;	/* argv[0] is the executable name */
	while (i < argc) {

		switch (argv[i][1]) {		/* assume -f style flags */
		case 'n':
			if (++i < argc)
				if(!sscanf(argv[i], "%d", &n)) {
				 	fprintf(stderr, "[ERROR] Could not read command line for -n!\n");
					return EXIT_FAILURE;
				}
			break;
		case 'k':
			if (++i < argc)
				if(!sscanf(argv[i], "%d", &k)) {
					fprintf(stderr, "[ERROR] Could not read command line for -k!\n");
					return EXIT_FAILURE;
				}
			break;
		default:
			fprintf(stderr, "cat poisbin.txt | %s [-n <int> -k <int>]\n"
				"\t-n <int>\tnumber of prob to be included\n"
				"\t-k <int>\tvalue of k\n",
        argv[0]);
			exit(EXIT_FAILURE);
		}
		++i;
	}

  // sscanf(argv[2], "%d", &n); // get n
  // sscanf(argv[4], "%d", &k); // get k

  char data;
  data = getchar();
  while(data != '\n'){
    data = getchar(); // read in data
  }

  float index[n];
  long double error[n];

  for (int i = 0; i < n; i++){
    scanf("%f %Lf", &index[i], &error[i]); // substantiate an n-length array of indices and error probabilities
  }


  int k_array[k];
  for (int i = 0; i < k; i++){
    k_array[i] = i;
  }

  long double diff_pi = 1.0;

  for (int i = 0; i < n; i++){
    diff_pi *= (1 - error[i]);
  }

  long double sumprod_w = 0.0;

  while (advance_array(k_array, k, n)) {
    sumprod_w += comp_w(k_array, error, k);
  }

  long double final = diff_pi * sumprod_w;

  printf("resulting pmf is %.18Le\n", final);

  return EXIT_SUCCESS;

}

long double comp_w(int *k_array, long double *error, int k){
  long double p_i;
  long double temp = 1.0;

  for (int i = 0; i < k; i++){

    p_i = error[k_array[i]];
    temp *= p_i / (1 - p_i);
  }

  return temp;
}

void set_to_inc_by_one(int*const array, const int index, const int length){
	int fill_value = array[index] + 1;
	for (int i=index+1; i<length; ++i) {
		array[i] = fill_value++;
	}
	return;
}

int advance_array(int*const array, const int length, const int max){
	int local_max = max -1;
	int success = 0;
	for (int adv_index = length-1; adv_index > -1; --adv_index) {
		if (array[adv_index] < local_max) {
			++array[adv_index];
			set_to_inc_by_one(array, adv_index, length);
			success = 1;
			break;
		}
		else {
			--local_max;
		}
	}
	return success;
}
