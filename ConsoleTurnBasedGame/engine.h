#include "data.h"

#ifndef ENGINE_H_   /* Include guard */
#define ENGINE_H_

#define CLASSCOUNT 4

Response Setup(Player *player1, Player *player2, Class *classes[CLASSCOUNT]);
int Engine(int running, Player player1, Player player2, Class *classes[CLASSCOUNT]);

#endif