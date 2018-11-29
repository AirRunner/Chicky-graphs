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
struct nodeSDL;

typedef enum selectedType
{
    ui,
    node,
    edge
}SelectedType;

typedef struct game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct renderingSLL *renderingSLL;
    SDL_Rect* selectedRect;
    SelectedType selectedType;
    struct nodeTree *texTree;
    int isrunning;
}Game;

void initSDL(Game* game, const char* title, int xpos, int ypos, int width, int height, int fullscreen);

void handleEvents(Game* game);

void mouseLeftPressed(Game* game, SDL_Event* event);
SDL_Rect* searchNodeUnderMouse(struct nodeSDL* nodes, SDL_Event* event);
void mouseLeftMove(Game* game, SDL_Event* event);
void mouseLeftReleased(Game* game, SDL_Event* event);

void update(Game* game);
void render(Game* game);
void cleanSDL(Game* game);

#endif
