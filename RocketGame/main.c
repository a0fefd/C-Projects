#include <stdio.h>

#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"

#include "loop.h"

/* Constants */
#define WIDTH 600
#define ASPECTRATIO 1/1
#define HEIGHT WIDTH/ASPECTRATIO


int main(int argc, char **argv) {
    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        0);

    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    loop(WIDTH, HEIGHT, renderer);

    SDL_Quit();

    return 0;
}
