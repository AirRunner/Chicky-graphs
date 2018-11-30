#include "sdl.h"

#include "renderingSLL.h"
#include "../controller/graphs.h"

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
                    case SDL_BUTTON_RIGHT:
                        mouseRightPressed(game, &event);
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
                    case SDL_BUTTON_RMASK:
                        mouseRightMove(game, &event);
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
                    case SDL_BUTTON_RIGHT:
                        mouseRightReleased(game, &event);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_C:
                        keyCPressed(game, &event);
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
    else
    {
        game->mouseLine = malloc(sizeof(SDL_Rect));
        game->mouseLine->x = game->mouseLine->w = event->motion.x;
        game->mouseLine->y = game->mouseLine->h = event->motion.y;
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
    //printf("Left Move!\n");
    if(game->selectedRect && game->selectedType == node)
    {
        //printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
        game->selectedRect->x += event->motion.xrel;
        game->selectedRect->y += event->motion.yrel;
    }
    if(game->mouseLine)
    {
        //printf("x1: %d, y1: %d, x2: %d, y2: %d\n", game->mouseLine->x, game->mouseLine->y, game->mouseLine->w, game->mouseLine->h);
        game->mouseLine->w += event->motion.xrel;
        game->mouseLine->h += event->motion.yrel;
    }
}

void mouseLeftReleased(Game* game, SDL_Event* event)
{
    printf("Left Released!\n");
    if(game->selectedRect)
    {
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
        game->selectedRect = NULL;
    }
    else if(game->mouseLine->x == game->mouseLine->w && game->mouseLine->y == game->mouseLine->h){
        createNode(game->graph, 0, &game->renderingSLL->nodes, createRect(game->mouseLine->x-32, game->mouseLine->y-32, 64, 64), searchTex(game->texTree, "Node", "Basic chick 1"));
        free(game->mouseLine);
        game->mouseLine = NULL;
    }
    else if(game->mouseLine)
    {
        checkEdgeCut(game, game->mouseLine, game->renderingSLL->edges, event);
        free(game->mouseLine);
        game->mouseLine = NULL;
    }
}

void mouseRightPressed(Game* game, SDL_Event* event)
{
    printf("Right Click!\n");
    game->selectedRect = searchNodeUnderMouse(game->renderingSLL->nodes, event);
    game->mouseLine = malloc(sizeof(SDL_Rect));
    game->mouseLine->x = game->mouseLine->w = event->motion.x;
    game->mouseLine->y = game->mouseLine->h = event->motion.y;
}

void mouseRightMove(Game* game, SDL_Event* event)
{
    if(game->mouseLine)
    {
        game->mouseLine->w += event->motion.xrel;
        game->mouseLine->h += event->motion.yrel;
    }
}

void mouseRightReleased(Game* game, SDL_Event* event){
    printf("Right Released!\n");
    if(game->mouseLine->x == game->mouseLine->w && game->mouseLine->y == game->mouseLine->h){
        deleteNode(game->graph, searchNode(game->graph, game->selectedRect), &game->renderingSLL->nodes, &game->renderingSLL->edges);
        free(game->mouseLine);
        game->mouseLine = NULL;
    }
    else if(game->selectedRect){
        free(game->mouseLine);
        game->mouseLine = searchNodeUnderMouse(game->renderingSLL->nodes, event);
        if(game->selectedRect != game->mouseLine){
            addEdge(game->graph, searchNode(game->graph, game->mouseLine), searchNode(game->graph, game->selectedRect), 1, &game->renderingSLL->edges, NULL);
        }
        game->mouseLine = NULL;
    }
}

void keyCPressed(Game* game, SDL_Event* event){
    printf("C Pressed!\n");
    contamination(game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges, game->texTree);
}

void checkEdgeCut(Game* game, SDL_Rect* mouseLine, EdgeSDL* edges, SDL_Event* event)
{
    int x1, y1, x2, y2;
    int a1, b1, a2, b2; //the coefficients for ax+b
    int xpoint, ypoint; //the point of intersection of the two ligns

    if(mouseLine->w != mouseLine->x)
    {
        if(mouseLine->x > mouseLine->w)
        {
            a1 = (mouseLine->h - mouseLine->y)/(mouseLine->w - mouseLine->x);
        }
        if(mouseLine->w < mouseLine->x)
        {
            a1 = (mouseLine->h - mouseLine->y)/(mouseLine->x - mouseLine->w);
        }
        b1 = a1*mouseLine->x - mouseLine->y;
    }

    while(edges)
    {
        x1 = edges->srcRect->x;
        y1 = edges->srcRect->y;
        x2 = edges->destRect->x;
        y2 = edges->destRect->y;

        if(x1 != x2)
        {
            if(x2 > x1)
            {
                a2 = (y2 - y1)/(x2 - x1); //calculations done on paper
            }
            if(x1 > x2)
            {
                a2 = (y2 - y1)/(x1 - x2);
            }
            b2 = a2*x1 - y1;

            if(a1 != a2 && mouseLine->w != mouseLine->x)
            {
                xpoint = (b2 - b1)/(a1 - a2); //calculations also done on paper
                ypoint = a1*xpoint + b1;
            }
            else if(mouseLine->w == mouseLine->x)
            {
                xpoint = mouseLine->x;
                ypoint = a2*xpoint + b2;
            }
            else
            {
                xpoint = -1;
                ypoint = -1;
            }
        }
        else
        {
            if(mouseLine->w != mouseLine->x)
            {
                xpoint = x1;
                ypoint = a1*xpoint + b1;
            }
            else
            {
                xpoint = -1;
                ypoint = -1;
            }
        }

        printf("xpoint: %d, ypoint: %d\n", xpoint, ypoint);

        if(xpoint != -1 && ypoint != -1)
        {
            if(((xpoint > x1 && xpoint < x2) || (xpoint < x1 && xpoint > x2)) && ((ypoint > y1 && ypoint < y2) || (ypoint < y1 && ypoint > y2)))
            {
                deleteEdge(game->graph, searchNode(game->graph, edges->srcRect), searchNode(game->graph, edges->destRect), &game->renderingSLL->edges);
            }
        }

        edges = edges->next;
    }
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
    if(game->mouseLine)
    {
        SDL_RenderDrawLine(game->renderer, game->mouseLine->x, game->mouseLine->y, game->mouseLine->w, game->mouseLine->h);
    }
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
