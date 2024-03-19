#include "data.h"

#ifndef ENGINE_H_   /* Include guard */
#define ENGINE_H_

void clrscr();

int Setup(struct Player player1, struct Player player2, struct Class classes[4]);
int Engine();

#endif