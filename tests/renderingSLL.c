#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct elt
{
    struct obj* obj; //pointer to the object to render
    struct elt* next;
}Elt;

typedef struct obj
{
    int id;
    SDL_Rect* rect; //pointer to the rect of the obj
    SDL_Texture* texture; //pointer to a texture stored in the texture tree
}Obj;

Elt* createElt(Obj* obj)
{
    Elt* newElt = (Elt*) malloc(sizeof(Elt));
    newElt->obj = obj;
    newElt->next = NULL;
    return newElt;
}

void addEltEnd(Elt* list, Obj* obj)
{
    if(list != NULL)
    {
        Elt* tmp = list;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = createElt(obj);
    }
    list = createElt(obj);
}

void addEltFirst(Elt** list, Obj* obj)
{
    Elt* tmp = createElt(obj);
    tmp->next = *list;
    *list = tmp;
}

void addElt(Elt** list, Obj* obj, int index)
{
    if(index <= 0 || *list == NULL)
    {
        Elt* tmp = createElt(obj);
        tmp->next = *list;
        *list = tmp;
    }
    else if(index > 0)
    {
        addElt(&(*list)->next, obj, index-1);
    }
}

void deleteElt(Elt** list, int id)
{
    if(*list != NULL)
    {
        if((*list)->obj->id == id)
        {
            Elt* tmp = *list;
            *list = (*list)->next;
            free(tmp);
        }
        else
        {
            deleteElt(&(*list)->next, id);
        }
    }
}

Obj* createObj(SDL_Rect* rect, SDL_Texture* texture)
{
    Obj* newObj = (Obj*) malloc(sizeof(Obj));
    newObj->rect = rect;
    newObj->texture = texture;
    return newObj;
}
int main()
{

    return 0;
}
