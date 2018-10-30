#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>

#include "sdl.h"


typedef struct elt
{
    struct node* child;
    struct elt* next;
}Elt;

typedef struct node
{
    char* name;
    SDL_Texture* texture;
    struct elt* children;
}Node;

Elt* createElt(Node* child);
Elt* freeSLL(Elt* children);

Node* createNode(char* name, SDL_Texture* texture);
void addChild(Node* parent, char* name, SDL_Texture* texture);
Node* freeTree(Node* node);

void printTreePrefixe(Node* root);


void initTex(Game* game, Node* textures);
SDL_Texture* createTex(Game* game, char* image);

#endif
