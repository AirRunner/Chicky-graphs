#include "renderingSLL.h"


RenderingSLL* createRenderingSLL()
{
    RenderingSLL* newRenderingSLL = malloc(sizeof(RenderingSLL));
    newRenderingSLL->edges = NULL;
    newRenderingSLL->nodes = NULL;
    newRenderingSLL->ui = NULL;
    return newRenderingSLL;
}

void initRenderingSLL()
{

}


EdgeSDL* createEdgeSDL(int type, NodeSDL* srcNode, NodeSDL* destNode, SDL_Texture* texArrow)
{
    EdgeSDL* newEdgeSDL = malloc(sizeof(EdgeSDL));
    newEdgeSDL->type = type;
    newEdgeSDL->srcNode = srcNode;
    newEdgeSDL->srcNode = srcNode;
    newEdgeSDL->texArrow = NULL;
    newEdgeSDL->next = NULL;
    return newEdgeSDL;
}

void addEdgeSDL(int type, EdgeSDL** edges, NodeSDL* srcNode, NodeSDL* destNode, SDL_Texture* texArrow)
{

}

void removeEdgeSDL(EdgeSDL** edges, NodeSDL* srcNode, NodeSDL* destNode)
{

}


NodeSDL* createNodeSDL(SDL_Rect* destRect, SDL_Texture* tex)
{
    NodeSDL* newNodeSDL = malloc(sizeof(NodeSDL));
    newNodeSDL->destRect = destRect;
    newNodeSDL->tex = tex;
    newNodeSDL->next = NULL;
    return newNodeSDL;
}

void addNodeSDL(NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex)
{

}

void removeNodeSDL(NodeSDL** nodes, SDL_Rect* destRect)
{

}


UI* createUI(SDL_Rect* destRect, SDL_Texture* tex)
{
    UI* newUI = malloc(sizeof(UI));
    newUI->destRect = destRect;
    newUI->tex = tex;
    newUI->next = NULL;
    return newUI;
}

void addUI(UI** nodes, SDL_Rect* destRect, SDL_Texture* tex)
{

}

void removeUI(UI** nodes, SDL_Rect* destRect)
{

}

