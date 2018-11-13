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

void initTex(Game* game, NodeTree* textures)
{
    textures = createNodeTree("Textures", NULL);
    addChild(textures, "Edge", NULL);
    addChild(textures, "Node", NULL);
    addChild(textures, "UI", NULL);

    EltTree* children = textures->children;
    NodeTree* tmp = children->child;

    addChild(tmp, "Line", createTex(game, ""));
    addChild(tmp, "Arrow", createTex(game, ""));

    children = children->next;
    tmp = children->child;

    addChild(tmp, "Chick 1", createTex(game, "../data/Chicks/Chick 1.png"));
    addChild(tmp, "Chick 2", createTex(game, "../data/Chicks/Chick 2.png"));
    addChild(tmp, "Chick 3", createTex(game, "../data/Chicks/Chick 3.png"));
    addChild(tmp, "Chick 4", createTex(game, "../data/Chicks/Chick 4.png"));
    addChild(tmp, "Chick 5", createTex(game, "../data/Chicks/Chick 5.png"));
    addChild(tmp, "Chick 6", createTex(game, "../data/Chicks/Chick 6.png"));
    addChild(tmp, "Chick 7", createTex(game, "../data/Chicks/Chick 7.png"));
    addChild(tmp, "Chick 8", createTex(game, "../data/Chicks/Chick 8.png"));
    addChild(tmp, "Chick 9", createTex(game, "../data/Chicks/Chick 9.png"));
    addChild(tmp, "Chick 10", createTex(game, "../data/Chicks/Chick 10.png"));
    addChild(tmp, "Chick 11", createTex(game, "../data/Chicks/Chick 11.png"));
    addChild(tmp, "Chick 12", createTex(game, "../data/Chicks/Chick 12.png"));
    addChild(tmp, "Chick 13", createTex(game, "../data/Chicks/Chick 13.png"));
    addChild(tmp, "Chick 14", createTex(game, "../data/Chicks/Chick 14.png"));
    addChild(tmp, "Chick 15", createTex(game, "../data/Chicks/Chick 15.png"));
    addChild(tmp, "Chick 16", createTex(game, "../data/Chicks/Chick 16.png"));

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
