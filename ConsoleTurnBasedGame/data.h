#include <string.h>
#include "keycodes.h"

#ifndef DATA_H_
#define DATA_H_

#define NONE (void)0

typedef struct Response
{
    char message[256];
    int ret;
} Response;

typedef struct Item 
{
    char name[20];
    char type;
    int healthDiff;
    int consumable;
} Item;

typedef struct Class 
{
    char name[20];
    float healthModifier;
    Item inv[8];
} Class;

typedef struct Player 
{
    int identifier;
    char type;
    int health;
    int maxHealth;
    int isTurn; 
    Class *playerClass;
} Player;

#endif