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