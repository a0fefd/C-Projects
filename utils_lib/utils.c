#include <string.h>
#include <stdio.h>
#include "utils.h"

// Clears the console screen.
void clrscr()
{
    // #if _WIN64 
    //     system("cls");
    // #elif _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    
    printf("\e[1;1H\e[2J");
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
    fread(f, sizeof(char), 1, stdin);
    fclose(f);
}

// Finds the index of an integer in an integer array.
int findIndexInt(int *arr, int target)
{
    size_t arrSize = sizeof(arr) / sizeof(int*);
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == target) 
        { 
            return i; 
        }
    }
    return -1;
}

// Finds the index of a character in a character array.
int findIndexChar(char *arr, char target)
{
    size_t arrSize = sizeof(arr) / sizeof(char*);
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == target) 
        { 
            return i; 
        }
    }
    return -1;
}

// Finds the index of a character string in a character string array.
int findIndexString(char **arr, char *target)
{
    size_t arrSize = sizeof(arr) / sizeof(char**);
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == target) 
        { 
            return i; 
        }
    }
    return -1;
}
