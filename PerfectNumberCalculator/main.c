#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int isPrime(int x)
{

    int singlePrimes[] = { 1, 2, 3, 5, 7 };
    for (int i = 0; i < sizeof(singlePrimes)/sizeof(int); i++) {
        if (x == singlePrimes[i]) { return 1; }
    }
    
    if (x % 2 == 0 || x % 3 == 0) { return 0; }

    for (int i = 3; i < (int)(x/3); i++) {
        if (x % i == 0) { return 0; } 
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int check = 0; int rank = 0;
    for (int i = 2; i < 64; i++) {
        check = isPrime(pow(2, i)-1);
        (check) ? rank++ : (void)0;
        (check) ? printf(
            "Rank %d; %d: %f\n", rank, i,
            ( pow( 2, (double)i) - 1 ) * pow( 2, (double)( i - 1 ) )
        ) : (void)0;
    }

    return 0;
}