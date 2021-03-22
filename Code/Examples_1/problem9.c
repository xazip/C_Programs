#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(void)
{
	int s = 1;
	int i = 0;
	
	for (i = 0; i <= 9; i++) {
		sleep(s);
		putchar(7);
		fflush(stdout);	
	}
	
	return EXIT_SUCCESS;
}
	
	
