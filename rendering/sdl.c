// Example program:
// Using SDL2 to create an application window

#include "sdl.h"

#include "renderingSLL.h"

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
                        mouseLeftPressed();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch(event.motion.state)
                {
                    case SDL_BUTTON_LMASK:
                        mouseLeftMove();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        mouseLeftReleased();
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void mouseLeftPressed()
{
    printf("Left Click!\n");
}

void mouseLeftReleased()
{
    printf("Left Released!\n");
}

void mouseLeftMove()
{
    printf("Left Move!\n");
}

void update(Game* game)
{

}

void render(Game* game)
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_RenderClear(game->renderer);
    //rendering stuff
    renderRenderingSLL(game->renderingSLL, game);
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
