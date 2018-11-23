#include <stdio.h>
#include <stdlib.h>

#include "../rendering/sdl.h"
#include "graphs.h"

void test(RenderingSLL* renderingSLL, NodeTree* texTree)
{
    Graph* graph = createGraph(5, 0);

    SDL_Texture* tex = texTree->children->next->child->children->child->texture;

    SDL_Rect* destRect = malloc(sizeof(SDL_Rect));
    destRect->x = 0;
    destRect->y = 0;
    destRect->h = 64;
    destRect->w = 64;

    createNode(graph, 1, &renderingSLL->nodes, destRect, tex);
    createNode(graph, 0, &renderingSLL->nodes, destRect, tex);
    createNode(graph, 0, &renderingSLL->nodes, destRect, tex);
    createNode(graph, 0, &renderingSLL->nodes, destRect, tex);
    createNode(graph, 0, &renderingSLL->nodes, destRect, tex);
    createNode(graph, 0, &renderingSLL->nodes, destRect, tex);

    addEdge(graph, 0, 1, 1, &renderingSLL->edges, tex);
    addEdge(graph, 0, 4, 1, &renderingSLL->edges, tex);
    addEdge(graph, 1, 2, 1, &renderingSLL->edges, tex);
    addEdge(graph, 1, 3, 1, &renderingSLL->edges, tex);
    addEdge(graph, 1, 4, 1, &renderingSLL->edges, tex);
    addEdge(graph, 2, 3, 1, &renderingSLL->edges, tex);
    addEdge(graph, 3, 4, 1, &renderingSLL->edges, tex);

    // Contamination test
    while(!isGraphEmpty(graph)){
        printGraph(graph);
        printNodes(graph);

        contamination(graph, &renderingSLL->nodes, &renderingSLL->edges);

        printNodes(graph);
    }
}

int main(int argc, char *argv[])
{

    Game* game = malloc(sizeof(Game));
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // a second devided by the number of frames per second
    int width = 1280, height = 720;

    initSDL
    (
        game,
        "Chicky graphs", //name of the window
        SDL_WINDOWPOS_CENTERED, //xposition of the window
        SDL_WINDOWPOS_CENTERED, //yposition of the window
        width, //width of the window
        height, //height of the window
        0 //fullscreen boolean
    );

    game->renderingSLL = createRenderingSLL();
    game->texTree = NULL;
    initTex(game, &game->texTree);

    test(game->renderingSLL, game->texTree);

    while(game->isrunning)
    {
        Uint32 frameStart = SDL_GetTicks();
        int frameTime;

        handleEvents(game);
        update(game);
        render(game);

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    cleanSDL(game);
    return 0;
}
