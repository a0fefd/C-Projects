#include "data.h"

#ifndef ENGINE_H_   /* Include guard */
#define ENGINE_H_

void clrscr();

Response Setup(Player *player1, Player *player2, Class classes[]);
int Engine(int running, Player player1, Player player2, Class classes[]);

#endif