#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int print_array(long double *arr, int k);
int check_arr(int *arr, int n, int k, int check_pos);
long double compute_w(int *arr, long double *err, int k);

int main(int argc, char *argv[]) {

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
    // int n, k;
    // char str_n[4];
    // char str_k[4];

    // sscanf(argv[1], "%s", str_n);
    // sscanf(argv[3], "%s", str_k);

    // if (strcmp(str_n, "-n") == 0) {
    //     sscanf(argv[2], "%d", &n);
    // }

    // if (strcmp(str_k, "-k") == 0) {
    //     sscanf(argv[4], "%d", &k);
    // }
    
    // loop the header
    char c;
    c = getchar();
    while(c != '\n') {
        c = getchar();
    }

    long double err[n];
    float idx[n];
    for (int i = 0; i < n; i++) {
        scanf("%f %Lf", &idx[i], &err[i]);    
    }

    long double pre_arr[k+2], cur_arr[k+2];
    pre_arr[0] = 1 - err[0];
    pre_arr[1] = err[0];

    if(k > 0) {
        for (int i = 2; i < k+2; i++) {
            pre_arr[i] = 0.0L;
        }
    }

    for (int i = 1; i < n; i++) {
        cur_arr[0] = (1 - err[i]) * pre_arr[0];
        for (int j = 1; j < (k+1); j++) {
            if(j > (i+1)) {
                cur_arr[j] = 0.0L;
            } else {
                cur_arr[j] = err[i] * pre_arr[j-1] + (1 - err[i]) * pre_arr[j];
                // if(i == 99 & j == 58) {
                //     printf("Now we are here: %Le = %Le * %Le + %Le * %Le\n", cur_arr[j], err[i], pre_arr[j-1], (1 - err[i]), pre_arr[j]);
                //     printf("and %Le * %Le = %Le\n", err[i], pre_arr[j-1], err[i] * pre_arr[j-1]);
                //     printf("%zu\n", sizeof((long double) pre_arr[j-1]));
                // }
            }
        }

        for (int m = 0; m < k+2; m++) {
            pre_arr[m] = cur_arr[m];
        }
    }

    // print_array(pre_arr, k+1);


    printf("the final pmf is %.18Le\n", pre_arr[k]);

    // long double test = 1.0L/3;
    // printf("%.20Lf\n", test);
    // printf("%zu\n", sizeof(1.2L));

    return 0;

}

long double compute_w(int *arr, long double *err, int k) {
    long double result = 1.0;
    long double pi;

    for (int i = 0; i < k; i++) {
        pi = err[arr[i]];
        result *= pi / (1 - pi);
    }

    return result;
}

int check_arr(int *arr, int n, int k, int check_pos) {
    if (check_pos < 0) {
        printf("never happened\n");
        return 0;
    }

    if (arr[check_pos] + 1 <= (check_pos + n - k)) {
        arr[check_pos] += 1;
        return 1;
    } else {
        if (check_pos == 0) return 0;
        arr[check_pos] = arr[check_pos - 1] + 2;

        for (int i = check_pos+1; i < k; i++) {
            arr[i] = arr[i-1] + 1;
        }
        
        return check_arr(arr, n, k, check_pos-1);
    }

}

int print_array(long double *arr, int k) {
    for (int i = 0; i < k; i++) {
        printf("%Le ", arr[i]);
    }
    printf("\n");
    return 0;
}

