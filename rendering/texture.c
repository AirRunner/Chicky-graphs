#include <string.h>
#include "texture.h"

EltTree* createEltTree(NodeTree* child)
{
    EltTree* newEltTree = (EltTree*) malloc(sizeof(EltTree));
    newEltTree->child = child;
    newEltTree->next = NULL;
    return newEltTree;
}

EltTree* freeSLL(EltTree* children)
{
    if(children == NULL)
    {
        return NULL;
    }
    else
    {
        freeSLL(children->next);
        free(children);
        return NULL;
    }
}


NodeTree* createNodeTree(char* name, SDL_Texture* texture)
{
    NodeTree* newNodeTree = (NodeTree*) malloc(sizeof(NodeTree));
    newNodeTree->texture = texture;
    newNodeTree->name = name;
    newNodeTree->children = NULL;
    return newNodeTree;
}

void addChild(NodeTree* parent, char* name, SDL_Texture* texture)
{
    NodeTree* newNodeTree = createNodeTree(name, texture);
    EltTree* newChild = createEltTree(newNodeTree);

    if(parent->children == NULL)
    {
        parent->children = newChild;
    }
    else
    {
        EltTree* tmp = parent->children;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newChild;
    }
}

NodeTree* freeTree(NodeTree* node)
{
    if(node->children == NULL)
    {
        free(node);
        return NULL;
    }
    else
    {
        EltTree* tmp = node->children;
        while(tmp != NULL)
        {
            freeTree(tmp->child);
            tmp = tmp->next;
        }
        node->children = freeSLL(node->children);
        free(node);
        return NULL;
    }
}


void printTreePrefixe(NodeTree* root)
{
    if(root != NULL)
    {
        printf("%s\n", root->name);
        EltTree* tmp = root->children;
        while(tmp != NULL)
        {
            printTreePrefixe(tmp->child);
            tmp = tmp->next;
        }
    }
}

void initTex(Game* game, NodeTree** textures)
{
    *textures = createNodeTree("Textures", NULL);
    addChild(*textures, "Edge", NULL);
    addChild(*textures, "Node", NULL);
    addChild(*textures, "UI", NULL);

    EltTree* children = (*textures)->children;
    NodeTree* tmp = children->child;

    //addChild(tmp, "Line", createTex(game, ""));
    //addChild(tmp, "Arrow", createTex(game, ""));

    children = children->next;
    tmp = children->child;

    addChild(tmp, "Bad answer chick", createTex(game, "../data/Assets/Chicks/Bad answer chick.png"));
    addChild(tmp, "Basic chick 1", createTex(game, "../data/Assets/Chicks/Basic chick 1.png"));
    addChild(tmp, "Basic chick 2", createTex(game, "../data/Assets/Chicks/Basic chick 2.png"));
    addChild(tmp, "Blink chick", createTex(game, "../data/Assets/Chicks/Blink chick.png"));
    addChild(tmp, "Boss chick", createTex(game, "../data/Assets/Chicks/Boss chick.png"));
    addChild(tmp, "Connected chick", createTex(game, "../data/Assets/Chicks/Connected chick.png"));
    addChild(tmp, "Dead chick", createTex(game, "../data/Assets/Chicks/Dead chick.png"));
    addChild(tmp, "Doubtful chick 1", createTex(game, "../data/Assets/Chicks/Doubtful chick 1.png"));
    addChild(tmp, "Doubtful chick 2", createTex(game, "../data/Assets/Chicks/Doubtful chick 2.png"));
    addChild(tmp, "Embarrassed chick", createTex(game, "../data/Assets/Chicks/Embarrassed chick.png"));
    addChild(tmp, "Happy chick", createTex(game, "../data/Assets/Chicks/Happy chick.png"));
    addChild(tmp, "Infected chick 1", createTex(game, "../data/Assets/Chicks/Infected chick 1.png"));
    addChild(tmp, "Infected chick 2", createTex(game, "../data/Assets/Chicks/Infected chick 2.png"));
    addChild(tmp, "Mocking chick", createTex(game, "../data/Assets/Chicks/Mocking chick.png"));
    addChild(tmp, "Success chick 1", createTex(game, "../data/Assets/Chicks/Success chick 1.png"));
    addChild(tmp, "Success chick 2", createTex(game, "../data/Assets/Chicks/Success chick 2.png"));
    addChild(tmp, "Surprised chick", createTex(game, "../data/Assets/Chicks/Surprised chick.png"));
    addChild(tmp, "Teacher chick 1", createTex(game, "../data/Assets/Chicks/Teacher chick 1.png"));
    addChild(tmp, "Teacher chick 2", createTex(game, "../data/Assets/Chicks/Teacher chick 2.png"));
    addChild(tmp, "Worried chick", createTex(game, "../data/Assets/Chicks/Worried chick.png"));

    children = children->next;
    tmp = children->child;

    //addChild(tmp, "Menu", createTex(game, "../data/UI/....png"));
}

SDL_Texture* createTex(Game* game, char* image)
{
    SDL_Surface* tmpS = IMG_Load(image);
    if(!tmpS)
    {
        SDL_Log("Unable to load Surface: %s", SDL_GetError());
        game->isrunning = 0;
        return NULL;
    }
    else
    {
        SDL_Texture* tmpT = SDL_CreateTextureFromSurface(game->renderer, tmpS);
        SDL_FreeSurface(tmpS);
        return tmpT;
    }
}

SDL_Texture* searchTex(NodeTree* textures, char* type, char* name){
    EltTree* children = textures->children;
    // Find the good type (edge, node or UI)
    while(children != NULL && strcmp(children->child->name, type)){
        children = children->next;
    }
    if(children == NULL){
        printf("Type not found: %s\n", type);
        return NULL;
    }
    children = children->child->children;
    //Find the good texture
    while(children != NULL && strcmp(children->child->name, name)){
        children = children->next;
    }
    if(children == NULL){
        printf("Texture not found: %s\n", name);
        return NULL;
    }
    return children->child->texture;
}
