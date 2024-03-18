#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int factorial(int n)
{
	int o = 1;
	for (int i = 1; i < n+1; i++) {
		o *= i;
	}
	
	return o;
}

int main(int argc, char *argv[])
{
	// define row and index vars
	// make pointers for row and index
	int row, index;
	int *rp = &row;
	int *ip = &index;

	// check if both of the required arguments exist
	if (argc > 2) {
		// define character arrays
		char n[8], r[8];
		
		// set the memory size for n and r and set all indexes to '\0'
		memset(n, '\0', sizeof(argv[1]));
		memset(r, '\0', sizeof(argv[2]));
		
		// set n, r to the 1st and 2nd arguments
		strcpy(n, argv[1]);
		strcpy(r, argv[2]);
		
		// set the row and index to the integer values in n and r
		*rp = atoi(n);
		*ip = atoi(r);
		
		// calculate nCr = n! / ( r!*(n-r)! )
		int combination = factorial(*rp) / ( factorial(*ip) * factorial(*rp - *ip) );
		
		// output the numbers to the console
		printf("COMB(%d, %d) = %d\n", *rp, *ip, combination);
	} else {
		// if there aren't enough arguments this is excecuted 
		puts("Error: 2 integer arguments required");
		puts("Usage: ./main <n: int> <r: int>");
		return -1;
	}
		

	return 0;
}

