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
struct edgeSDL;
struct ui;
struct graph;
struct text;

typedef enum MissionNumber{
    Menu,
    Mission1,
    Mission2,
    Mission3,
    Mission4,
    Mission5,
    Mission6,
    Mission7,
    Mission8,
    Mission9,
    Mission10,
    Mission11,
    Mission12,
    Sandbox
}MissionNumber;

typedef enum selectedType
{
    node,
    edge,
    UInext,
    UImenu,
    UIsandbox,
    UInewGame,
    UIresumeGame
}SelectedType;

typedef struct game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct ui *background;
    struct renderingSLL *renderingSLL;
    SDL_Rect* selectedRect;
    SelectedType selectedType;
    struct nodeTree *texTree;
    struct graph* graph;
    SDL_Rect* mouseLine;
    struct text* text;
    MissionNumber missionNumber;
    int isrunning;
}Game;

void initSDL(Game* game, const char* title, int xpos, int ypos, int width, int height, int fullscreen);

void handleEvents(Game* game);

SDL_Rect* searchNodeUnderMouse(struct nodeSDL* nodes, SDL_Event* event);
void searchUIUnderMouse(Game* game, SDL_Event* event);

void mouseLeftPressed(Game* game, SDL_Event* event);
void mouseLeftMove(Game* game, SDL_Event* event);
void mouseLeftReleased(Game* game, SDL_Event* event);

void mouseRightPressed(Game* game, SDL_Event* event);
void mouseRightMove(Game* game, SDL_Event* event);
void mouseRightReleased(Game* game, SDL_Event* event);

char* missionToStr(MissionNumber nbMission);
MissionNumber strToMission(char *str);

void buttonNewGamePressed(Game* game);
void buttonMenuPressed(Game* game);
void buttonSandboxPressed(Game* game);
void buttonNextPressed(Game* game);
void buttonResumePressed(Game* game);

void keyCPressed(Game* game, SDL_Event* event);
void keyIPressed(Game* game, SDL_Event* event);
void checkEdgeCut(Game* game, SDL_Rect* mouseLine, struct edgeSDL* edges, SDL_Event* event);

void update(Game* game);
void render(Game* game);
void cleanSDL(Game* game);

#endif
