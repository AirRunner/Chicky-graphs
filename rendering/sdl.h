#ifndef SDL_H
#define SDL_H

#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

struct renderingSLL;
struct nodeTree;

typedef struct game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct renderingSLL *renderingSLL;
    struct nodeTree *texTree;
    int isrunning;
}Game;

void initSDL(Game* game, const char* title, int xpos, int ypos, int width, int height, int fullscreen);

void handleEvents(Game* game);

void mouseLeftPressed();
void mouseLeftReleased();
void mouseLeftMove();

void update(Game* game);
void render(Game* game);
void cleanSDL(Game* game);

#endif
