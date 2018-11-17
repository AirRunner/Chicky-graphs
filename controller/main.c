#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "../rendering/sdl.h"
#include "graphs.h"

void test(RenderingSLL* renderingSLL, SDL_Texture* tex)
{
    Graph* graph = createGraph(5, 0);

    createNode(graph, 1, &renderingSLL->nodes, tex);
    createNode(graph, 0, &renderingSLL->nodes, tex);
    createNode(graph, 0, &renderingSLL->nodes, tex);
    createNode(graph, 0, &renderingSLL->nodes, tex);
    createNode(graph, 0, &renderingSLL->nodes, tex);
    createNode(graph, 0, &renderingSLL->nodes, tex);

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

    RenderingSLL* renderingSLL = createRenderingSLL();

    test(renderingSLL, NULL);

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
    return 0;
}
