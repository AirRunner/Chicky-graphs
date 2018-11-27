#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>

typedef struct game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    struct renderingSLL *renderingSLL;
    struct nodeTree *texTree;
    int isrunning;
}Game;

void initSDL(Game* game, const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
    game->isrunning = 1;
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
        game->isrunning = 0;
    }

    if(game->isrunning)
    {
        game->window = SDL_CreateWindow(
                title,
                xpos,
                ypos,
                width,
                height,
                flags);
    
        if(!game->window)
        {
            SDL_Log("Unable to initialize the Window: %s", SDL_GetError());
            SDL_Quit();
            game->isrunning = 0;
        }
    }
    
    if(game->isrunning)
    {
        game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
        if(!game->renderer)
        {
            SDL_Log("Unable to initialize the renderer: %s", SDL_GetError());
            SDL_DestroyWindow(game->window);
            SDL_Quit();
            game->isrunning = 0;
        }
    }

    if(game->isrunning)
    {
        if(TTF_Init() != 0)
        {
            SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
            TTF_Quit();
            game->isrunning = 0;
        }
    }
}

void handleEvents(Game* game)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                game->isrunning = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        printf("Click\n");
                        break;
                    default:
                        break;
                }
        }
    }
}

void update(Game* game)
{

}

void render(Game* game, SDL_Texture* tex, SDL_Rect* destRect)
{
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, tex, NULL, destRect);
    SDL_RenderPresent(game->renderer);
}

void cleanSDL(Game* game)
{
    if(game->renderer)
    {
        SDL_DestroyRenderer(game->renderer);
    }
    if(game->window)
    {
        SDL_DestroyWindow(game->window);
    }
    TTF_Quit();
    SDL_Quit();
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

    SDL_Surface* tmpS = IMG_Load("../../data/Assets/Chicks/Bad answer chick.png");
    SDL_Texture* tmpT;
    if(!tmpS)
    {
        SDL_Log("Unable to load Surface: %s", SDL_GetError());
        game->isrunning = 0;
    }
    else
    {
        tmpT = SDL_CreateTextureFromSurface(game->renderer, tmpS);
        SDL_FreeSurface(tmpS);
    }

    SDL_Rect* destRect = malloc(sizeof(SDL_Rect));
    destRect->x = 0;
    destRect->y = 0;
    destRect->h = 64;
    destRect->w = 64;

    while(game->isrunning)
    {
        Uint32 frameStart = SDL_GetTicks();
        int frameTime;

        handleEvents(game);
        update(game);
        render(game, tmpT, destRect);

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    cleanSDL(game);
    return 0;
}
