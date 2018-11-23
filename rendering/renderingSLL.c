#include "renderingSLL.h"


RenderingSLL* createRenderingSLL()
{
    RenderingSLL* newRenderingSLL = malloc(sizeof(RenderingSLL));
    newRenderingSLL->edges = NULL;
    newRenderingSLL->nodes = NULL;
    newRenderingSLL->ui = NULL;
    return newRenderingSLL;
}

void renderRenderingSLL(RenderingSLL* renderingSLL, Game* game)
{
    renderEdges(renderingSLL->edges, game);
    renderNodes(renderingSLL->nodes, game);
    renderUI(renderingSLL->ui, game);
}


EdgeSDL* createEdgeSDL(int directed, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_Texture* texArrow)
{
    EdgeSDL* newEdgeSDL = malloc(sizeof(EdgeSDL));
    newEdgeSDL->directed = directed;
    newEdgeSDL->srcRect = srcRect;
    newEdgeSDL->destRect = destRect;
    newEdgeSDL->texArrow = NULL;
    newEdgeSDL->next = NULL;
    return newEdgeSDL;
}

void addEdgeSDL(int directed, EdgeSDL** edges, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_Texture* texArrow)
{
    EdgeSDL* newEdgeSDL = createEdgeSDL(directed, srcRect, destRect, texArrow);
    if(!*edges)
        *edges = newEdgeSDL;
    else
    {
        EdgeSDL* tmp = *edges;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = newEdgeSDL;
    }
}

void removeEdgeSDL(EdgeSDL** edges, SDL_Rect* srcRect, SDL_Rect* destRect)
{
    if(*edges)
    {
        EdgeSDL* tmp = *edges;
        if((*edges)->srcRect == srcRect && (*edges)->destRect == destRect)
        {
            *edges = (*edges)->next;
            free(tmp);
        }
        else
        {
            while(tmp->next != NULL && (tmp->next->srcRect != srcRect || tmp->next->destRect != destRect))
            {
                tmp = tmp->next;
            }
            if(tmp->next)
            {
                EdgeSDL* freetmp = tmp->next;
                tmp->next = tmp->next->next;
                free(freetmp);
            }
        }
    }
}

void renderEdges(EdgeSDL* edges, Game* game)
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

NodeSDL* addNodeSDL(NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex)
{
    NodeSDL* newNodeSDL = createNodeSDL(destRect, tex);
    if(!*nodes)
        *nodes = newNodeSDL;
    else
    {
        NodeSDL* tmp = *nodes;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = newNodeSDL;
    }
    return newNodeSDL;
}

void removeNodeSDL(NodeSDL** nodes, SDL_Rect* destRect)
{
    if(*nodes)
    {
        NodeSDL* tmp = *nodes;
        if((*nodes)->destRect == destRect)
        {
            *nodes = (*nodes)->next;
            free(tmp);
        }
        else
        {
            while(tmp->next != NULL && tmp->next->destRect != destRect)
            {
                tmp = tmp->next;
            }
            if(tmp->next)
            {
                NodeSDL* freetmp = tmp->next;
                tmp->next = tmp->next->next;
                free(freetmp);
            }
        }
    }
}

void renderNodes(NodeSDL* nodes, Game* game)
{
    while(nodes)
    {
        SDL_RenderCopy(game->renderer, nodes->tex, NULL, nodes->destRect);
        nodes = nodes->next;
    }
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
    UI* newUI = createUI(destRect, tex);
    if(!*nodes)
        *nodes = newUI;
    else
    {
        UI* tmp = *nodes;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = newUI;
    }
}

void removeUI(UI** nodes, SDL_Rect* destRect)
{
    if(*nodes)
    {
        UI* tmp = *nodes;
        if((*nodes)->destRect == destRect)
        {
            *nodes = (*nodes)->next;
            free(tmp);
        }
        else
        {
            while(tmp->next != NULL && tmp->next->destRect != destRect)
            {
                tmp = tmp->next;
            }
            if(tmp->next)
            {
                UI* freetmp = tmp->next;
                tmp->next = tmp->next->next;
                free(freetmp);
            }
        }
    }
}

void renderUI(UI* ui, Game* game)
{

}
