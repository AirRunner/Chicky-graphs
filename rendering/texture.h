#ifndef TEXTURE_H
#define TEXTURE_H

#include "sdl.h"

typedef struct eltTree
{
    struct nodeTree* child;
    struct eltTree* next;
}EltTree;

typedef struct nodeTree
{
    char* name;
    SDL_Texture* texture;
    struct eltTree* children;
}NodeTree;

EltTree* createEltTree(NodeTree* child);
EltTree* freeSLL(EltTree* children);

NodeTree* createNodeTree(char* name, SDL_Texture* texture);
void addChild(NodeTree* parent, char* name, SDL_Texture* texture);
NodeTree* freeTree(NodeTree* node);

void printTreePrefixe(NodeTree* root);


void initTex(Game* game, NodeTree** textures);
SDL_Texture* createTex(Game* game, char* image);
SDL_Texture* searchTex(NodeTree* textures, char* type, char* name);

#endif
