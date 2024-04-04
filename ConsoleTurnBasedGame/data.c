#include <string.h>
#include <stdio.h>
#include "data.h"

void setVoid()
{
    strcpy(VOID.name, " ");
    (&VOID)->type = 'V';
    (&VOID)->healthDiff = 0;
    (&VOID)->consumable = 0;
}