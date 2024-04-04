#include <string.h>
#include <stdio.h>
#include "utils.h"

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

void invert(int *var)
{
    *var = !*var;
}

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
