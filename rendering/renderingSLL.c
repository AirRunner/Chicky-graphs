#include <string.h>
#include <math.h>
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
    while(edges)
    {
        float x1, y1, x2, y2;
        x1 = edges->srcRect->x + edges->srcRect->w/2;
        y1 = edges->srcRect->y + edges->srcRect->h/2;
        x2 = edges->destRect->x + edges->destRect->w/2;
        y2 = edges->destRect->y + edges->destRect->h/2;
        SDL_RenderDrawLine(game->renderer, x1, y1, x2, y2);
        if(edges->directed)
        {
            float xTopArrow, yTopArrow, aLine, aPerpLine, bPerpLine, xInter, yInter, distance, xLeftArrow, yLeftArrow, xRightArrow, yRightArrow;
            xTopArrow = x1 + 2*(x2-x1)/3;
            yTopArrow = y1 + 2*(y2-y1)/3;
            xInter = x1 + 7*(x2-x1)/12;
            yInter = y1 + 7*(y2-y1)/12;
            distance = 20;
            if(x1 != x2)
            {
                aLine = (y2 - y1)/(x2 - x1);
                if(aLine)
                {
                    aPerpLine = -1/aLine;
                    bPerpLine =  yInter - aPerpLine*xInter;
                    xLeftArrow = xInter + distance/(sqrtf(1+aPerpLine*aPerpLine));
                    yLeftArrow = aPerpLine*xLeftArrow + bPerpLine;
                    xRightArrow = xInter - distance/(sqrtf(1+aPerpLine*aPerpLine));
                    yRightArrow = aPerpLine*xRightArrow + bPerpLine;
                }
                else
                {
                    xLeftArrow = xRightArrow = xInter;
                    yLeftArrow = yInter + distance;
                    yRightArrow = yInter - distance;
                }
            }
            else
            {
                yLeftArrow = yRightArrow = yInter;
                xLeftArrow = xInter - distance;
                xRightArrow = xInter + distance;
            }
            SDL_RenderDrawLine(game->renderer, xLeftArrow, yLeftArrow, xTopArrow, yTopArrow);
            SDL_RenderDrawLine(game->renderer, xRightArrow, yRightArrow, xTopArrow, yTopArrow);
        }
        edges = edges->next;
    }
}


NodeSDL* createNodeSDL(SDL_Rect* destRect, SDL_Texture* tex)
{
    NodeSDL* newNodeSDL = (NodeSDL*) malloc(sizeof(NodeSDL));
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
            free(tmp->destRect);
            tmp->destRect = NULL;
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
                free(freetmp->destRect);
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

void changeTexture(NodeSDL* node, NodeTree* texTree, char* texName){
    int w, h;
    SDL_QueryTexture(searchTex(texTree, "Node", texName), NULL, NULL, &w, &h);

    if(strstr(texName, "eacher")){
        w /= 2; h /= 2;
    }
    else{
        w /= 4; h /= 4;
    }
    // Resize the SDL Rect
    node->destRect->x -= (w-node->destRect->w)/2;
    node->destRect->y -= (h-node->destRect->h)/2;
    node->destRect->w = w;
    node->destRect->h = h;
    // Change texture
    node->tex = searchTex(texTree, "Node", texName);
}


UI* createUI(SDL_Rect* destRect, SDL_Texture* tex, UIType type)
{
    UI* newUI = malloc(sizeof(UI));
    newUI->destRect = destRect;
    newUI->tex = tex;
    newUI->type = type;
    newUI->next = NULL;
    return newUI;
}

void addUI(UI** nodes, SDL_Rect* destRect, SDL_Texture* tex, UIType type)
{
    UI* newUI = createUI(destRect, tex, type);
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

void deleteUISLL(UI** nodes){
    while(*nodes){
        UI* tmp = *nodes;
        *nodes = (*nodes)->next;
        free(tmp);
    }
}

void renderUI(UI* ui, Game* game)
{
    while(ui)
    {
        SDL_RenderCopy(game->renderer, ui->tex, NULL, ui->destRect);
        ui = ui->next;
    }
}


SDL_Rect* createRect(int x, int y, int w, int h)
{
    SDL_Rect* newRect = malloc(sizeof(SDL_Rect));
    newRect->x = x;
    newRect->y = y;
    newRect->w = w;
    newRect->h = h;
    return newRect;
}
