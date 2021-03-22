#include <stdio.h>
#include <stdlib.h>


typedef unsigned long long uint64_t;

int main(int argc, char *argv[]){
  typedef struct _substr {
    uint64_t sid;        /*!< 2-bit mapping for substrings <=32 chars */
    struct substr *next; /*!< pointer to next element in bucket */
    unsigned int cnt;    /*!< count of this substring */
  } substr;
  
  if (argc < 6) {
    fprintf(stderr, "Invalid usage.\n");
    return EXIT_FAILURE;
  }
  
  int l = atoi(argv[2]);
  int t = atoi(argv[4]);
  unsigned int power4 = 1 << 2*l;
  if (l <= 0 || l > 11){
    fprintf(stderr, "[ERROR] We must have 0 < l <= 10 for integer l for increased performance\n");
    return EXIT_FAILURE;
  }
  else{
    printf("l = %d\n", l);
    printf("4^l = %d\n", power4);
  }
  
  substr *ht;
  ht = (substr*)calloc(t, sizeof(substr));
  if (ht == NULL) { 
    fprintf(stderr, "[ERROR] Memory not allocated.\n"); 
    return EXIT_FAILURE; 
  } 
  char c;
  unsigned int nseq = 0; /* Counter for number of substrings processed */
  char substring[l];
  substr *head;
  FILE *fp;
  fp = fopen(argv[5], "r");
  if (fp == NULL){
    printf("Error! File not read.\n");
    return EXIT_FAILURE;
  }
  int loc = 0; /* Index tracker for first l characters on a line */
  while ((c = fgetc(fp)) != '\n'); // Skips first line in file
  do{
    while ( loc < l ){
      c = fgetc(fp); // reading the file
      substring[loc] = c;
      ++loc;
    }
    
    /* In case the last line of the file ends in a newline */
    if (feof(fp))
      break;
    
    //int i = 0;
    uint64_t i = 0;
    /* Mapping is A = 00, C = 01, G = 11, T = 10 */
    /* Convert chraracter substring to integer index for count_arr */
    for (int j = 0; j < l; ++j){
      if(substring[j] == 'C'){
        i = i | 1 << (2 * (l - 1 - j));
      }
      else if(substring[j] == 'G'){
        i = i | 3 << (2 * (l - 1 - j));
      }
      else if(substring[j] == 'T'){
        i = i | 2 << (2 * (l - 1 - j));
      }
    }
    
    int b = i % t; // Get bucket for substring
    
    if(ht[b].cnt == 0){ /* Empty bucket */ // This does fill!
      ht[b].sid = i;
      ht[b].next = NULL;
      ht[b].cnt = 1;
      //printf("start bucket = %d, id = %llu\n", b, i);
    }
    else{
      /* The bucket isn't empty!*/
      head = &(ht[b]); // Pointer to head of list
      while(1){
        if(head->sid == i){
          head->cnt += 1;
          //printf("Duplicate found!\n");
          break;
        }
        else{
          if(head->next != NULL){
            /* Advance to next node */
            head = head->next;
          }
          if(head->next == NULL && head->sid != i){
            /* Allocate new struct */
            substr *temp;
            temp = (substr*) malloc(sizeof(substr));
            if (temp == NULL){
              fprintf(stderr, "[ERROR] Memory not allocated.\n"); 
              return EXIT_FAILURE;
            }
            /* Put in data */
            temp->sid = i;
            temp->next = NULL;
            temp->cnt = 1;
            head->next = temp;
            head = NULL;
            //printf("new: bucket = %d, id = %llu\n", b, i);
            break;
          }
      }
    }
      }
    
    /*Advance forward on the line*/
    for(int n = 1; n < l; n++){
      substring[n - 1] = substring[n];
    }
    /* Read next char from file */
    substring[l - 1] = fgetc(fp);
    
    /* Check if we've reached the end of the file or string */
    if (feof(fp) || substring[l - 1] == '\n') {
      c = fgetc(fp);	/* Look for possible last line */
    if (feof(fp))
      break;
    while ((c = fgetc(fp)) != '\n'); /* Skip the next line */
    loc = 0;	/* Reset loc */
    i = 0; /* Reset i */
    ++nseq; /* Advance substring counter */
    if (!(nseq % 100000)) putc('.', stderr); /* Track progress */
    }
  } while (!feof(fp));
  putc('\n', stderr);
  fclose(fp); /* Close file */
  printf("Substring count complete!\n");
  fflush(stdout);
  int bucket = 0;
  int count = 0;
  for(bucket = 0; bucket < t; bucket++){
    substr *pos = &ht[bucket];
    while(pos != NULL){
      count++;
      pos = pos->next;
    }
  }
  printf("Number of unique substrings in file: %d\n", count);
  printf("Proportion of possible substrings observed: %g\n", (double)count/power4);
  free(ht);
  return EXIT_SUCCESS;
}
