#ifndef RENDERINGSLL_H
#define RENDERINGSLL_H

#include "texture.h"

typedef struct renderingSLL
{
    struct edgeSDL* edges;
    struct nodeSDL* nodes;
    struct ui* ui;
} RenderingSLL;

typedef struct edgeSDL
{
    int directed;
    SDL_Rect* srcRect;
    SDL_Rect* destRect;
    SDL_Texture* texArrow;
    struct edgeSDL* next;
}EdgeSDL;

typedef struct nodeSDL
{
    SDL_Rect* destRect;
    SDL_Texture* tex;
    struct nodeSDL* next;
}NodeSDL;

typedef enum uiType
{
    next,
    menu,
    sandbox,
    newGame,
    resumeGame,
    background,
    other
}UIType;

typedef struct ui
{
    SDL_Rect* destRect;
    SDL_Texture* tex;
    struct ui* next;
    UIType type;
}UI;

RenderingSLL* createRenderingSLL();
void renderRenderingSLL(RenderingSLL* renderingSLL, Game* game);

EdgeSDL* createEdgeSDL(int directed, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_Texture* texArrow);
void addEdgeSDL(int directed, EdgeSDL** edges, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_Texture* texArrow);
void removeEdgeSDL(EdgeSDL** edges, SDL_Rect* srcRect, SDL_Rect* destRect);
void renderEdges(EdgeSDL* edges, Game* game);

NodeSDL* createNodeSDL(SDL_Rect* destRect, SDL_Texture* tex);
NodeSDL* addNodeSDL(NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex);
void removeNodeSDL(NodeSDL** nodes, SDL_Rect* destRect);
void renderNodes(NodeSDL* nodes, Game* game);

void changeTexture(NodeSDL* node, NodeTree* texTree, char* texName);

UI* createUI(SDL_Rect* destRect, SDL_Texture* tex, UIType type);
void addUI(UI** nodes, SDL_Rect* destRect, SDL_Texture* tex, UIType type);
void removeUI(UI** nodes, SDL_Rect* destRect);
void renderUI(UI* ui, Game* game);

SDL_Rect* createRect(int x, int y, int w, int h);

#endif
