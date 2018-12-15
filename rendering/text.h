#ifndef TEXT_H
#define TEXT_H value

#include "SDL_FontCache.h"
#include "../data-layer/data.h"

typedef struct text
{
    TextSLL* textSLL;
    FC_Font* font;
    FC_Rect destRect;
}Text;

Text* createText(TextSLL* textSLL, FC_Font* font, int x, int y, int w, int h);
void renderText(Game* game);
#endif /* ifndef TEXT_H */
