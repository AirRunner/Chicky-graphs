#ifndef SDL_H
#define SDL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

struct renderingSLL;

typedef struct game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct renderingSLL *renderingSLL;
    int isrunning;
}Game;

void initSDL(Game* game, const char* title, int xpos, int ypos, int width, int height, int fullscreen);
void handleEvents(Game* game);
void update(Game* game);
void render(Game* game);
void cleanSDL(Game* game);

#endif
