#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "array.h"


int main(int argc, char *argv[]) {
  char filename[100];
  int count = 0;
  char c;

  if(!sscanf(argv[1], "%99s", filename)) {
    fprintf(stderr, "[ERROR] Could not read command line for the matrix txt file!\n");
    return EXIT_FAILURE;
  }

  FILE *path;
  path = fopen(filename, "r");

  if (path == NULL) {
    printf("error couldn't open file\n");
    return EXIT_FAILURE;
  }

  // used from geeksforgeeks.org/c-program-count-number-lines-file/
  // since we can assume a square m x m matrix,
  //    finding the length of the text file is equal to finding the number of rows and columns.

  for (c = getc(path); c != EOF; c = getc(path)) {
    if (c == '\n') {
      count++;
    }
  }
  /////////////////////////////////////////////////////////////////

  if (count<=0){
    fprintf(stderr, "[ERROR] The value of m is incorrect");
    return EXIT_FAILURE;
  } 


  rewind(path);

  path = fopen(filename, "r");

//   double **matrix = (double **)malloc(count * sizeof(double*));
//   for (int row = 0; row < count; row++){
//     matrix[row] = (double *)malloc(count * sizeof(double));
//   }

  double **matrix;
  MAKE_2ARRAY(matrix, count, count);

  while(!feof(path)) {
    for (int col = 0; col < count; col++){
      for (int row = 0; row < count; row++){
        fscanf(path, "%lf", &matrix[row][col]);
      }
    }
  }

//   printf("qmatrix: \n");
//   for (int row = 0; row < count; ++row){
//     for (int col = 0; col < count; ++col){
//       printf("%lf ", matrix[row][col]);
//     }
//     printf("\n");
//   }

  // initialize x0 at n=0;
  double *xn, *xn_plus;
  xn = malloc(count * sizeof(*xn));
  xn_plus = malloc(count * sizeof(*xn_plus));

  for (int i = 0; i < count; i++){
    xn[i] = 1.0 / count;
    xn_plus[i] = 1.0 / count;
  }

  // do-while loop to calculate x_{n+1} and make sure that (x_{n+1} - x_{n}) ^ 2 > epsiolon

  double epsilon = 0.00001;
  double difference_check = 0;

  do {
    //reset xn
    for (int i = 0; i < count; i++){
      xn[i] = xn_plus[i];
    }

    //calculate xn_plus[i]
    for (int i = 0; i < count; i++){
      double dot_prod = 0.0;

      for (int j = 0; j < count; j++){
        dot_prod += matrix[i][j] * xn[j];
      }

      xn_plus[i] = dot_prod;
    }

    // calculate squared error (to account for pos/neg values canceling each other out and reporting low loss)
    difference_check = 0; // reset the difference from last loop
    for (int i = 0; i < count; i++){
      difference_check += (xn_plus[i] - xn[i])*(xn_plus[i] - xn[i]);
    }

  } while (difference_check > epsilon);

  printf("stationary distribution: ");
  for (int i = 0; i < count; i++){
    printf("%lf ", xn_plus[i]);
  }

  printf("\n");

  fclose(path);

  if(matrix) 
    FREE_2ARRAY(matrix);  
  
  if(xn)
    FREE_1ARRAY(xn);

  if(xn_plus)
    FREE_1ARRAY(xn_plus);

  return EXIT_SUCCESS;
}
