#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int factorial(int n)
{
	long long int o = 1;

	for (int i = 1; i < n+1; i++) {
		o *= i;
	}
	
	return o;
}

long int calculate(char type, int n, int r)
{
    long int o = factorial(n) / factorial (n - r);

    if (type == 'C') {
        return o / factorial(r);
    }
    
    return o;
}

int main(int argc, char *argv[])
{
    int row, index;
    int *rp = &row;
    int *ip = &index;

    if (argc > 1) {
        char n[8], r[8];

        memset(n, '\0', sizeof(n));
        memset(r, '\0', sizeof(r));

        char *argv1 = malloc( sizeof(argv[1]) / sizeof(char) );
        strcpy(argv1, argv[1]);

        char *ret = strtok_r(argv[1], "PC", &argv[1]);
        char *type = strtok_r(argv1, "0123456789", &argv1);

        strcpy(n, ret);
        strcpy(r, ret + (strlen(ret)+1)*sizeof(char));

        *rp = atoi(n);
        *ip = atoi(r);

        long output = calculate(*type, *rp, *ip);

        char output_s[5];
        if (*type == 'C') {
            strcpy(output_s, "COMB");
        } else {
            strcpy(output_s, "PERM");
        }

        printf("%s(%d, %d) = %d\n", output_s, *rp, *ip, output);
    }
}