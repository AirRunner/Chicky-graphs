#include <stdio.h>
#include <stdlib.h>

#include "../rendering/sdl.h"
#include "graphs.h"

void test(Graph* graph, RenderingSLL* renderingSLL, NodeTree* texTree)
{
    int h, w;
    h = w = 64;

    createNode(graph, 1, &renderingSLL->nodes, createRect(0, 0, h, w), searchTex(texTree, "Node", "Infected chick 2"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(2*h, 0, h, w), searchTex(texTree, "Node", "Basic chick 1"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(4*h, h, h, w), searchTex(texTree, "Node", "Basic chick 1"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(2*h, 2*h, h, w), searchTex(texTree, "Node", "Basic chick 1"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(0, 2*h, h, w), searchTex(texTree, "Node", "Basic chick 1"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(0, 4*h, h, w), searchTex(texTree, "Node", "Basic chick 1"));

    addEdge(graph, 0, 1, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 0, 4, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 1, 2, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 1, 3, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 1, 4, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 2, 3, 1, &renderingSLL->edges, NULL);
    addEdge(graph, 3, 4, 1, &renderingSLL->edges, NULL);
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
    game->graph = createGraph(5, 0);

    test(game->graph, game->renderingSLL, game->texTree);

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

    deleteGraph(&game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges);

    cleanSDL(game);
    return 0;
}
