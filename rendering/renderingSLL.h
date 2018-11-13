#ifndef RENDERINGSLL_H
#define RENDERINGSLL_H

#include "sdl.h"
#include "texture.h"

typedef struct renderingSLL
{
    struct edgeSDL* edges;
    struct nodeSDL* nodes;
    struct ui* ui;
} RenderingSLL;

typedef struct edgeSDL
{
    int type;
    struct nodeSDL* srcNode;
    struct nodeSDL* destNode;
    SDL_Texture* texArrow;
    struct edgeSDL* next;
}EdgeSDL;

typedef struct nodeSDL
{
    SDL_Rect* destRect;
    SDL_Texture* tex;
    struct nodeSDL* next;
}NodeSDL;

typedef struct ui
{
    SDL_Rect* destRect;
    SDL_Texture* tex;
    struct ui* next;
}UI;

RenderingSLL* createRenderingSLL();
void initRenderingSLL();

EdgeSDL* createEdgeSDL(int type, NodeSDL* srcNode, NodeSDL* destNode, SDL_Texture* texArrow);
void addEdgeSDL(int type, EdgeSDL** edges, NodeSDL* srcNode, NodeSDL* destNode, SDL_Texture* texArrow);
void removeEdgeSDL(EdgeSDL** edges, NodeSDL* srcNode, NodeSDL* destNode);

NodeSDL* createNodeSDL(SDL_Rect* destRect, SDL_Texture* tex);
void addNodeSDL(NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex);
void removeNodeSDL(NodeSDL** nodes, SDL_Rect* destRect);

UI* createUI(SDL_Rect* destRect, SDL_Texture* tex);
void addUI(UI** nodes, SDL_Rect* destRect, SDL_Texture* tex);
void removeUI(UI** nodes, SDL_Rect* destRect);

#endif
