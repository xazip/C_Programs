#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "array.h"

void compress_array(unsigned char* arr, int col, int row, unsigned char* arr_n, int col_n, int row_n, unsigned int d);

int main(int argc, char *argv[]) {
    char ppm_name[100], d_input[100];
    unsigned char val;
    unsigned char *red, *green, *blue;
    unsigned char *red_n, *green_n, *blue_n;

    unsigned int d = 0;

    if(argc < 2) {
        fprintf(stderr, "[ERROR] the ppm file name was not provided!\n"
                "please try ./compress xxx.ppm\n");
        return EXIT_FAILURE;
    }

    if(!sscanf(argv[1], "%99s", ppm_name)) {
        fprintf(stderr, "[ERROR] Could not read command line for the ppm file!\n");
        return EXIT_FAILURE;
    }

    FILE *fp, *out;
    int output_idx = 0;
    char out_buf[100];

    char c;

    char *line = NULL;
    size_t len = 0;

    int col, row, col_n, row_n;

    fp = fopen(ppm_name, "r");
    if(fp == NULL) {
        printf("failed to open\n");
        return(EXIT_FAILURE);
    }

    while(1) {
        printf("Please enter a neighborhood size (0, 1, 2, ...) or e(x)it > ");
        scanf("%99s", d_input);
        if(strcmp(d_input, "x") == 0) {
            break;
        } else {
            d = (unsigned int) atoi(d_input);
            // printf("the value of d: %u\n", d);

            rewind(fp);

            // skip P3
            do { c = fgetc(fp);
            } while (c != '\n');


            do { 
                c = fgetc(fp);
                if(c == '#') {
                    // printf("comment found\n");
                    do { c = fgetc(fp);
                    } while (c != '\n');
                    break;
                } else {
                    // printf("comment not found\n");
                    fseek(fp, -1L, SEEK_CUR);
                    break;
                }
            } while (c != '\n');

            // take col and row
            getline(&line, &len, fp);
            sscanf(line, "%d %d", &col, &row);
            // printf("the input col and row: %d, %d\n", col, row);

            col_n = col / (2*d+1);
            row_n = row / (2*d+1);

            if(col_n == 0 || row_n == 0) {
                fprintf(stderr, "[ERROR] Please try a positive value for d "
                "that doesn't exceed the dimension of your ppm file!\n");
                return EXIT_FAILURE;
            }
            
            // printf("the input col_n and row_n: %d, %d\n", col_n, row_n);

            MAKE_1ARRAY(red, col * row);
            MAKE_1ARRAY(green, col * row);
            MAKE_1ARRAY(blue, col * row);

            MAKE_1ARRAY(red_n, col_n * row_n);
            MAKE_1ARRAY(green_n, col_n * row_n);
            MAKE_1ARRAY(blue_n, col_n * row_n);
            // take 255
            getline(&line, &len, fp);
            
            // setup for the output
            snprintf(out_buf, 100, "compress_%d_%s", output_idx++, ppm_name);
            out = fopen(out_buf, "w+");
            fprintf(out, "P3\n%d %d\n255\n", col_n, row_n);

            ssize_t read;
            for(int i = 0; i < col * row * 3; ++i) {
                if((read = getline(&line, &len, fp)) == -1)
                    break;
                val = atoi(line);
                if( i % 3 == 0) {
                    red[i / 3] = val;
                } else if (i % 3 == 1) {
                    green[i / 3] = val;
                } else if (i % 3 == 2) {
                    blue[i / 3] = val;
                }
                // printf("the read in value is: %d\n", val);
                
            }

            compress_array(red, col, row, red_n, col_n, row_n, d);
            compress_array(green, col, row, green_n, col_n, row_n, d);
            compress_array(blue, col, row, blue_n, col_n, row_n, d);

            for(int j = 0; j < col_n*row_n*3; ++j) {
                if( j % 3 == 0) {
                    fprintf(out, "%d\n", red_n[j/3]);
                } else if (j % 3 == 1) {
                    fprintf(out, "%d\n", green_n[j/3]);
                } else if (j % 3 == 2) {
                    fprintf(out, "%d\n", blue_n[j/3]);
                } else {
                    fprintf(stderr, "Unexpected Error. Impossible in terms of logic.\n");
                }
            }

            printf("The output is %s in the current directory.\n", out_buf);

            fclose(out);

            FREE_1ARRAY(red);
            FREE_1ARRAY(green);
            FREE_1ARRAY(blue);
        }
    }

    fclose(fp);
    
    if(line)            
        free(line);

    return EXIT_SUCCESS;
}

void compress_array(unsigned char* arr, int col, int row, unsigned char* arr_n, int col_n, int row_n, unsigned int d){
    unsigned int square = 2 * d + 1;
    int sum, k_end, l_end;
    unsigned char check_result;
    for (int i = 0; i < row_n; ++i) {
        for(int j = 0; j < col_n; ++j) {
            sum = 0;
            k_end = i*square + square;
            l_end = j*square + square;

            if(i == row_n-1) {
                k_end += row % square;
            }

            if(j == col_n - 1) {
                l_end += col % square;
            }

            for (int k = i*square; k < k_end; ++k) {
                for (int l = j*square; l < l_end; ++l) {
                    sum += arr[k*col+l];
                }
            }

            check_result = sum / ((k_end - i*square) * (l_end - j*square));
            if(check_result > 255) {
                fprintf(stderr, "check result: %d\nsum: %d\n denominator:%d\n", check_result, sum, ((k_end - i*square) * (l_end - j*square)));
            }
            arr_n[i*col_n + j] = check_result;
        }
    }

}
