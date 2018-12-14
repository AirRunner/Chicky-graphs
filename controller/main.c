#include "graphs.h"
#include "../data-layer/data.h"
#include "../rendering/text.h"

void test(Graph* graph, RenderingSLL* renderingSLL, NodeTree* texTree)
{
    int w, h, wi, hi;
    SDL_QueryTexture(searchTex(texTree, "Node", "Basic chick"), NULL, NULL, &w, &h);
    SDL_QueryTexture(searchTex(texTree, "Node", "Infected chick 4"), NULL, NULL, &wi, &hi);
    w /= 4; h /= 4;
    wi /= 4; hi /= 4;
    // Testing graph
    createNode(graph, 0, &renderingSLL->nodes, createRect(0, 0, w, h), searchTex(texTree, "Node", "Basic chick"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(2*h, 0, w, h), searchTex(texTree, "Node", "Basic chick"));
    createNode(graph, 1, &renderingSLL->nodes, createRect(4*h-20, h-20, wi, hi), searchTex(texTree, "Node", "Infected chick 4"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(2*h, 2*h, w, h), searchTex(texTree, "Node", "Basic chick"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(0, 2*h, w, h), searchTex(texTree, "Node", "Basic chick"));
    createNode(graph, 0, &renderingSLL->nodes, createRect(0, 4*h, wi*2, hi*2), searchTex(texTree, "Node", "Teacher chick 1"));

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
    FC_Font* font = FC_CreateFont();
    FC_LoadFont(font, game->renderer, "../data/fonts/NotoSansMono-Regular.ttf", 18, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
    game->text = NULL;
    game->missionNumber = Menu;

    //game->graph = createGraph(10, 0);
    //test(game->graph, game->renderingSLL, game->texTree);

    initTex(game);
    loadMission(game);


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
