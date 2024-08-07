//
// Created by nbigi0 on 7/08/2024.
//

#ifndef ENGINE_H
#define ENGINE_H

#endif //ENGINE_H

#include "../include/SDL2/SDL.h"

struct velStruct {
    int x;
    int y;
};
#define Velocity struct velStruct

enum playerStateEnum {
    NONE,
    BOOSTING,
    CLOCKWISEROT,
    CCLOCKWISEROT
};
#define PlayerState enum playerStateEnum

struct plrStruct {
    SDL_Texture *texture;
    int x;
    int y;
    double angle;
    Velocity vel;
    PlayerState state;
};
#define Player struct plrStruct

Player initPlayer(SDL_Renderer *renderer, SDL_Surface *textureSurface, int x, int y, Velocity vel);
Velocity initVelocity(int x, int y);
SDL_Colour createColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void clearVelocity(Player *player);
void clearScreen(SDL_Renderer *renderer);
void renderPlayer(SDL_Renderer *renderer, Player player, SDL_Rect *textureRect, SDL_Point *point);
void updatePlayerCoordinates(Player *player, int maxX, int maxY);
void configurePlayerMotion(Player *player);
double toRad(double degrees);