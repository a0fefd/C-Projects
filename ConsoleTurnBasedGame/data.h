#include <string.h>
#include "keycodes.h"

#ifndef DATA_H_
#define DATA_H_

#define NONE (void)0

struct _Response
{
    char message[256];
    int ret;
};
typedef struct _Response Response;

struct _Item 
{
    char name[20];
    char type;
    int healthDiff;
    int consumable;
};
typedef struct _Item Item;

struct _Effect 
{
    int healthDiff;
    float healthMulti;
    int damageDiff;
    float damageMulti;
};
typedef struct _Effect Effect;

struct _ClassAbility
{
    char name[64];
    char message[64];
    int delay;
    Effect effect;
};
typedef struct _ClassAbility ClassAbility;

struct _Class 
{
    char name[20];
    float healthModifier;
    ClassAbility ability;
    Item inv[8];
};
typedef struct _Class Class;

struct _Player 
{
    int identifier;
    char type;
    int health;
    int isTurn; 
    Class *playerClass;
};
typedef struct _Player Player;

#endif