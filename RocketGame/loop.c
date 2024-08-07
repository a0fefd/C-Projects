//
// Created by nbigi0 on 7/08/2024.
//
#include <sys/time.h>
#include <stdio.h>
#include "include/SDL2/SDL.h"

#include "loop.h"
#include "engine/engine.h"

void setRectPos(SDL_Rect *rect, const int x, const int y) {
    rect->x = x;
    rect->y = y;
}

void loop(int winWidth, int winHeight, SDL_Renderer *renderer) {
    Player player = initPlayer(renderer, SDL_LoadBMP("../assets/Player.bmp"), 0, 0,
        initVelocity(0, 0));
    SDL_Point point;
    point.x = 34/2; point.y = 50/2;

    SDL_Rect textureRect;
    textureRect.x = 0; textureRect.y = 0;

    double fps = 0;
    struct timeval t1, t2;
    double elapsedTime = 0;

    SDL_Event event;
    int running = 1;
    while (running) {
        clearScreen(renderer);

        /* FPS CALC */
        fps = 1000/elapsedTime;
        // printf("FPS: %f\n", fps);
        gettimeofday(&t1, NULL);
        /* FPS CALC */

        printf("x: %d, player: %d\n", point.x, player.x);
        printf("x: %d, player: %d\n", point.y, player.y);
        printf("ang: %f\n", player.angle);

        configurePlayerMotion(&player);
        updatePlayerCoordinates(&player, winWidth, winHeight);
        renderPlayer(renderer, player, &textureRect, &point);

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;

                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        player.state = BOOSTING;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        player.state = CCLOCKWISEROT;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        player.state = CLOCKWISEROT;
                    }

                    break;
                }

                default: {
                    break;
                }

                case SDL_KEYUP: {
                    player.state = NONE;
                    break;
                }
            }
        }

        SDL_RenderPresent(renderer);

        // FPS CALC
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    }
}