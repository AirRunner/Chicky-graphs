#include "sdl.h"
#include "../controller/graphs.h"
#include "text.h"
#include "../data-layer/data.h"

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
                    case SDL_SCANCODE_I:
                        keyIPressed(game, &event);
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
    // Search a node under the mouse
    game->selectedRect = searchNodeUnderMouse(game->renderingSLL->nodes, event);
    printf("x: %d, y: %d\n", event->motion.x, event->motion.y);
    if(game->selectedRect)
    {
        // Select the node if there is one
        game->selectedType = node;
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
    }
    else
    {
        searchUIUnderMouse(game, event);
    }
    if(!game->selectedRect)
    {
        // Create a line otherwise
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

        SDL_GetMouseState(&xm, &ym);
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

void searchUIUnderMouse(Game* game, SDL_Event* event)
{
    int x, y, w, h, xm, ym;
    UI* ui = game->renderingSLL->ui;
    if(ui)
    {
        x = ui->destRect->x;
        y = ui->destRect->y;
        w = ui->destRect->w;
        h = ui->destRect->h;

        SDL_GetMouseState(&xm, &ym);
        while(ui->next && ((xm < x || xm > x+w) || (ym < y || ym > y+h)))
        {
            ui = ui->next;
            x = ui->destRect->x;
            y = ui->destRect->y;
            w = ui->destRect->w;
            h = ui->destRect->h;
        }
        if(ui && ((xm > x && xm < x+w) && (ym > y && ym < y+h)))
        {
            switch(ui->type)
            {
                case next:
                    game->selectedRect = ui->destRect;
                    game->selectedType = UInext;
                    break;
                case menu:
                    game->selectedRect = ui->destRect;
                    game->selectedType = UImenu;
                    break;
                case sandbox:
                    game->selectedRect = ui->destRect;
                    game->selectedType = UIsandbox;
                    break;
                case newGame:
                    game->selectedRect = ui->destRect;
                    game->selectedType = UInewGame;
                    break;
                case resumeGame:
                    game->selectedRect = ui->destRect;
                    game->selectedType = UIresumeGame;
                    break;
                default:
                    break;
            }
        }
        else
        {
            game->selectedRect = NULL;
        }
    }
    else
    {
        game->selectedRect = NULL;
    }
}

void mouseLeftMove(Game* game, SDL_Event* event)
{
    if(game->selectedRect && game->selectedType == node)
    {
        // Move the node
        game->selectedRect->x += event->motion.xrel;
        game->selectedRect->y += event->motion.yrel;
        if(textureRect(game, game->selectedRect) == searchTex(game->texTree, "Node", "Teacher chick 1")){
            changeTexture(game->graph->array[searchNode(game->graph, game->selectedRect)]->nodeSDL, game->texTree, "Angry teacher 3");
        }
    }
    if(game->mouseLine)
    {
        // Move the line
        game->mouseLine->w += event->motion.xrel;
        game->mouseLine->h += event->motion.yrel;
    }
}

void mouseLeftReleased(Game* game, SDL_Event* event)
{
    printf("Left Released!\n");
    if(game->selectedRect && game->selectedType == node)
    {
        // Release the node
        if(textureRect(game, game->selectedRect) == searchTex(game->texTree, "Node", "Angry teacher 3")){
            changeTexture(game->graph->array[searchNode(game->graph, game->selectedRect)]->nodeSDL, game->texTree, "Teacher chick 1");
        }
        printf("x: %d, y: %d\n", game->selectedRect->x, game->selectedRect->y);
        game->selectedRect = NULL;
    }
    else if(game->selectedRect)
    {
        //release the mouse when at first he pressed a ui element
        SDL_Rect* tmp = game->selectedRect;
        searchUIUnderMouse(game, event);
        if(game->selectedRect == tmp)
        {
            //actions for the buttons
            if(game->selectedType == UInext)
            {
                //does something for the specific button
            }
            else if(game->selectedType == UImenu)
            {
                buttonMenuPressed(game);
            }
            else if(game->selectedType == UIsandbox)
            {
                buttonSandboxPressed(game);
            }
            else if(game->selectedType == UInewGame)
            {
                buttonNewGamePressed(game);
            }
            else if(game->selectedType == UIresumeGame)
            {
                //does something for the specific button
            }
        }
        game->selectedRect = NULL;
    }
    else if(game->mouseLine->x == game->mouseLine->w && game->mouseLine->y == game->mouseLine->h){
        // Create a node
        int w, h;
        SDL_QueryTexture(searchTex(game->texTree, "Node", "Basic chick"), NULL, NULL, &w, &h);
        w /= 4; h /= 4;
        createNode(game->graph, 0, &game->renderingSLL->nodes, createRect(game->mouseLine->x-w/2, game->mouseLine->y-h/2, w, h), searchTex(game->texTree, "Node", "Basic chick"));
        free(game->mouseLine);
        game->mouseLine = NULL;
    }
    else if(game->mouseLine)
    {
        // Cut an edge
        checkEdgeCut(game, game->mouseLine, game->renderingSLL->edges, event);
        free(game->mouseLine);
        game->mouseLine = NULL;
    }
}

void mouseRightPressed(Game* game, SDL_Event* event)
{
    printf("Right Click!\n");
    game->selectedRect = searchNodeUnderMouse(game->renderingSLL->nodes, event);
    if(game->selectedRect){
        game->mouseLine = malloc(sizeof(SDL_Rect));
        game->mouseLine->x = game->mouseLine->w = event->motion.x;
        game->mouseLine->y = game->mouseLine->h = event->motion.y;
    }
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
    if(game->mouseLine && game->selectedRect){
        if(game->mouseLine->x == game->mouseLine->w && game->mouseLine->y == game->mouseLine->h){
            // Delete the node if it's not a teacher
            if(textureRect(game, game->selectedRect) != searchTex(game->texTree, "Node", "Teacher chick 1")){
                deleteNode(game->graph, searchNode(game->graph, game->selectedRect), &game->renderingSLL->nodes, &game->renderingSLL->edges);
            }
            free(game->mouseLine);
        }
        else{
            free(game->mouseLine);
            game->mouseLine = searchNodeUnderMouse(game->renderingSLL->nodes, event);
            if(game->mouseLine && game->selectedRect != game->mouseLine){
                // Add an edge
                addEdge(game->graph, searchNode(game->graph, game->mouseLine), searchNode(game->graph, game->selectedRect), 1, &game->renderingSLL->edges, NULL);
            }
        }
        game->mouseLine = NULL;
        game->selectedRect = NULL;
    }
}

void buttonNewGamePressed(Game* game){
    game->missionNumber = Mission1;
    deleteGraph(&game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges);
    deleteUISLL(&game->renderingSLL->ui);
    loadMission(game);
}

void buttonMenuPressed(Game* game){
    game->missionNumber = Menu;
    deleteGraph(&game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges);
    deleteUISLL(&game->renderingSLL->ui);
    loadMission(game);
}

void buttonSandboxPressed(Game* game){
    game->missionNumber = Sandbox;
    deleteGraph(&game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges);
    deleteUISLL(&game->renderingSLL->ui);
    loadMission(game);
}

void keyCPressed(Game* game, SDL_Event* event){
    printf("C Pressed!\n");
    contamination(game->graph, &game->renderingSLL->nodes, &game->renderingSLL->edges, game->texTree);
}

void keyIPressed(Game* game, SDL_Event* event){
    printf("I Pressed!\n");
    game->selectedRect = searchNodeUnderMouse(game->renderingSLL->nodes, event);
    if(game->selectedRect){
        if(game->graph->array[searchNode(game->graph, game->selectedRect)]->node->data == 0){
            // Infect the node if it's not a teacher
            if(textureRect(game, game->selectedRect) != searchTex(game->texTree, "Node", "Teacher chick 1")){
                game->graph->array[searchNode(game->graph, game->selectedRect)]->node->data = 1;
                changeTexture(game->graph->array[searchNode(game->graph, game->selectedRect)]->nodeSDL, game->texTree, "Infected chick 4");
            }
        }
        else{
            // Disinfect the node
            game->graph->array[searchNode(game->graph, game->selectedRect)]->node->data = 0;
            changeTexture(game->graph->array[searchNode(game->graph, game->selectedRect)]->nodeSDL, game->texTree, "Basic chick");
        }
    }
}

void checkEdgeCut(Game* game, SDL_Rect* mouseLine, EdgeSDL* edges, SDL_Event* event)
{
    float x1, y1, x2, y2;
    float a1, b1, a2, b2; //the coefficients for ax+b
    float xpoint, ypoint; //the point of intersection of the two ligns

    if(mouseLine->w != mouseLine->x)
    {
        a1 = (float)(mouseLine->h - mouseLine->y)/(float)(mouseLine->w - mouseLine->x);
        b1 = mouseLine->y - a1*(float)mouseLine->x;
    }

    while(edges)
    {
        x1 = edges->srcRect->x + edges->srcRect->w/2;
        y1 = edges->srcRect->y + edges->srcRect->h/2;
        x2 = edges->destRect->x + edges->srcRect->w/2;
        y2 = edges->destRect->y + edges->srcRect->h/2;

        if(x1 != x2)
        {
            a2 = (y2 - y1)/(x2 - x1); //calculations done on paper
            b2 = y1 - a2*x1;

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

        printf("x1: %f, y1: %f, x2: %f, y2: %f\n", x1, y1, x2, y2);
        printf("xpoint: %f, ypoint: %f\n", xpoint, ypoint);

        if(xpoint != -1 && ypoint != -1)
        {
            if(((xpoint >= x1 && xpoint <= x2) || (xpoint <= x1 && xpoint >= x2)) && ((ypoint >= y1 && ypoint <= y2) || (ypoint <= y1 && ypoint >= y2)) && ((xpoint >= mouseLine->x && xpoint <= mouseLine->w) || (xpoint <= mouseLine->x && xpoint >= mouseLine->w)) && ((ypoint >= mouseLine->y && ypoint <= mouseLine->h) || (ypoint <= mouseLine->y && ypoint >= mouseLine->h)))
            {
                deleteEdge(game->graph, searchNode(game->graph, edges->srcRect), searchNode(game->graph, edges->destRect), &game->renderingSLL->edges);
                deleteEdge(game->graph, searchNode(game->graph, edges->destRect), searchNode(game->graph, edges->srcRect), &game->renderingSLL->edges);
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
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(game->renderer, game->background->tex, NULL, game->background->destRect);
    if(game->mouseLine)
    {
        SDL_RenderDrawLine(game->renderer, game->mouseLine->x, game->mouseLine->y, game->mouseLine->w, game->mouseLine->h);
    }
    renderRenderingSLL(game->renderingSLL, game);

    renderText(game);

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
