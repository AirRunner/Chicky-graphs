#include "graphs.h"
#include "../data-layer/data.h"
#include "../rendering/text.h"

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
    game->text = createText(NULL, font, 400, 585, 703, 800);
    game->missionNumber = Menu;

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
