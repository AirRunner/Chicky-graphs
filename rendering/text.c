#include "text.h"


Text* createText(TextSLL* textSLL, FC_Font* font, int x, int y, int w, int h)
{
    Text* newText = malloc(sizeof(Text));
    newText->textSLL = textSLL;
    newText->font = font;
    newText->destRect.x = x;
    newText->destRect.y = y;
    newText->destRect.w = w;
    newText->destRect.h = h;
    
    return newText;
}

void renderText(Game* game)
{
    if(game->text)
    {
        // Print chicks' id on them
        if(game->missionNumber == Mission5 || game->missionNumber == Mission6 ||
            game->missionNumber == Mission8 || game->missionNumber == Mission9){
            printID(game);
        }
        
        if(game->text->textSLL){
            //SDL_RenderSetClipRect(game->renderer, &game->text->destRect);
            FC_DrawBoxAlign(game->text->font, game->renderer, game->text->destRect, FC_ALIGN_CENTER, game->text->textSLL->text);
            //SDL_RenderSetClipRect(game->renderer, NULL);
        }
    }
}
