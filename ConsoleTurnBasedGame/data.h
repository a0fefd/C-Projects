#ifndef DATA_H_
#define DATA_H_

struct Item 
{
    char name[20];
    char type;
    int healthDiff;
};

struct Effect 
{
    int healthDiff;
    float healthMulti;
    int damageDiff;
    float damageMulti;
};

struct ClassAbility
{
    char name[64];
    char message[64];
    int delay;
    struct Effect effect;
};

struct Class 
{
    char name[20];
    float healthModifier;
    struct ClassAbility ability;
    struct Item inv[8];
};

struct Player 
{
    int identifier;
    char type;
    int health;
    int isTurn; 
    struct Class playerClass;
};

#endif