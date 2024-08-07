//
// Created by nbigi0 on 7/08/2024.
//

#include "engine.h"

#include <math.h>

#define BOOST_STRENGTH 7
#define ROT_SPEED 5.0
#define PI 3.141592653589

Player initPlayer(SDL_Renderer *renderer, SDL_Surface *textureSurface, const int x, const int y, const Velocity vel) {
    Player returnPlayer;
    returnPlayer.texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    returnPlayer.x = x;
    returnPlayer.y = y;
    returnPlayer.angle = 0.0;
    returnPlayer.vel = vel;
    returnPlayer.state = NONE;
    return returnPlayer;
}
Velocity initVelocity(const int x, const int y) {
    Velocity returnVelocity;
    returnVelocity.x = x;
    returnVelocity.y = y;
    return returnVelocity;
}
SDL_Colour createColour(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
    SDL_Colour returnColour;
    returnColour.r = r;
    returnColour.g = g;
    returnColour.b = b;
    returnColour.a = a;
    return returnColour;
}

void clearVelocity(Player *player) {
    Velocity zeroVelocity;
    zeroVelocity.x = 0;
    zeroVelocity.y = 0;
    player->vel = zeroVelocity;
}

void clearScreen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void renderPlayer(SDL_Renderer *renderer, Player player, SDL_Rect *textureRect, SDL_Point *point) {
    textureRect->x = player.x;
    textureRect->y = player.y;
    textureRect->w = 34;
    textureRect->h = 50;

    SDL_RenderClear(renderer);
    // SDL_RenderCopy(renderer, player.texture, NULL, &textureRect);
    SDL_RenderCopyEx(renderer, player.texture, NULL, textureRect, player.angle, point, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

void updatePlayerCoordinates(Player *player, int maxX, int maxY) {
    if (!(player->x < maxX-BOOST_STRENGTH-34/2 && player->y < maxY-BOOST_STRENGTH-50/2 && player->x > 0 && player->y > 0)) {
        if (player->x >= maxX-BOOST_STRENGTH-34/2) {
            player->x -= 1;
        }
        if (player->y >= maxY-BOOST_STRENGTH-50/2) {
            player->y -= 1;
        }
        if (player->x <= 0) {
            player->x += 1;
        }
        if (player->y <= 0) {
            player->y += 1;
        }
    } else {
        player->x += player->vel.x;
        player->y += player->vel.y;
    }

}

void configurePlayerMotion(Player *player) {
    if (player->state == NONE) {
        player->vel = initVelocity(0, 0);
    } else if (player->state == BOOSTING) {
        player->vel.x = BOOST_STRENGTH * -1*cos(toRad(player->angle) + PI/2);
        player->vel.y = BOOST_STRENGTH * -1*sin(toRad(player->angle) + PI/2);
    } else if (player->state == CLOCKWISEROT) {
        player->angle += ROT_SPEED;
    } else if (player->state == CCLOCKWISEROT) {
        player->angle -= ROT_SPEED;
    }
}

double toRad(double degrees) {
    return degrees * PI/180;
}
