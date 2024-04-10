#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Clears the console screen.
void clrscr()
{
    
    #if _WIN64 
        system("cls");
    #elif _WIN32
        system("cls");
    #else
        printf("\e[1;1H\e[2J");
        // system("clear");
    #endif
}

// Inverts an integer.
//
// int i = 1;
// printf("Normal: %d \n", i); // Outputs 1
// invert( &i );
// printf("Inverted: %d \n", i); // Outputs 0
void invert(int *var)
{
    *var = !*var;
}

// Pauses the console with message "Press Enter to continue..."
// Continues when enter is pressed.
void pauseEnter()
{
     printf("\n\nPress Enter to continue...");

    FILE *f = tmpfile();
    // it can take any char but it instantly continues when enter is pressed so...
    fread(f, sizeof(char), 1, stdin);
    fclose(f);  
}

int isPrime(int num)
{
	int factorCountThing = (int) ( (num + 1) / 2 );

	int factors[factorCountThing];
    memset(factors, 0, sizeof(factors));

    int index = 0;
    for (int n = 2; n < factorCountThing; n++)
    {
        if (num % n == 0) 
        {
            factors[index] = n;
            index++;
        }
    }

    if (factors[0] != 0)
    {
        return 0;
    }

    return 1;
}

long long int factorial(int num)
{
	long long int out = 1;

	for (int i = 1; i < num + 1; i++) {
		out *= i;
	}
	
	return out;
}

