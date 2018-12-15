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
EltTree* addChild(NodeTree* parent, char* name, SDL_Texture* texture);
NodeTree* freeTree(NodeTree* node);

void printTreePrefixe(NodeTree* root);

void loadTex(FILE* file, Game* game, NodeTree* texTree, char* type);
void initTex(Game* game);
SDL_Texture* createTex(Game* game, char* image);
SDL_Texture* searchTex(NodeTree* textures, char* type, char* name);
SDL_Texture* textureRect(Game* game, SDL_Rect* rect);
char* nextTex(NodeTree* textures, SDL_Texture* currTex);

#endif
