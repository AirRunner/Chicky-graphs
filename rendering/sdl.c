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
    game->selectedRect = NULL;
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
                        mouseLeftPressed(game, &event);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch(event.motion.state)
                {
                    case SDL_BUTTON_LMASK:
                        mouseLeftMove(game, &event);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        mouseLeftReleased(game, &event);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void mouseLeftPressed(Game* game, SDL_Event* event)
{
    printf("Left Click!\n");
    game->selectedRect = searchNodeUnderMouse(game->renderingSLL->nodes, event);
    printf("x: %d, y: %d\n", event->motion.x, event->motion.y);
    if(game->selectedRect)
    {
        game->selectedType = node;
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
    }
}

SDL_Rect* searchNodeUnderMouse(struct nodeSDL* nodes, SDL_Event* event)
{
    int x, y, w, h, xm, ym;
    if(nodes)
    {
        x = nodes->destRect->x;
        y = nodes->destRect->y;
        w = nodes->destRect->w;
        h = nodes->destRect->h;

        xm = event->button.x;
        ym = event->button.y;
        while(nodes->next && ((xm < x || xm > x+w) || (ym < y || ym > y+h)))
        {
            nodes = nodes->next;
            x = nodes->destRect->x;
            y = nodes->destRect->y;
            w = nodes->destRect->w;
            h = nodes->destRect->h;
        }
        if(nodes && ((xm > x && xm < x+w) && (ym > y && ym < y+h)))
        {
            return nodes->destRect;
        }
    }
    return NULL;
}

void mouseLeftMove(Game* game, SDL_Event* event)
{
    printf("Left Move!\n");
    if(game->selectedRect)
    {
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
        game->selectedRect->x += event->motion.xrel;
        game->selectedRect->y += event->motion.yrel;
    }
}

void mouseLeftReleased(Game* game, SDL_Event* event)
{
    printf("Left Released!\n");
    if(game->selectedRect)
    {
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
    }
    game->selectedRect = NULL;
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
