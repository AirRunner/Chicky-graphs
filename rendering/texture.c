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

// Import name and path of a texture from a file
void loadTex(FILE* file, Game* game, NodeTree* tmp){
    char* name = malloc(50 * sizeof(char));
    char* tex = malloc(100 * sizeof(char));
    fgets(name, 50, file); name[strlen(name)-1] = '\0';
    fgets(tex, 100, file); tex[strlen(tex)-1] = '\0';
    addChild(tmp, name, createTex(game, tex));
}

void initTex(Game* game, NodeTree** textures)
{
    FILE* file = NULL;
    file = fopen("../data/Assets/importTextures.txt","r");
    char* type = malloc(10 * sizeof(char));

    *textures = createNodeTree("Textures", NULL);
    addChild(*textures, "Edge", NULL);
    addChild(*textures, "Node", NULL);
    addChild(*textures, "UI", NULL);

    EltTree* children = (*textures)->children;
    NodeTree* tmp = children->child;
    // Import edges
    fgets(type, 10, file);
    while(strcmp(type, "Node\n")){
        loadTex(file, game, tmp);
        fgets(type, 10, file);
    }

    children = children->next;
    tmp = children->child;
    // Import nodes
    while(strcmp(type, "UI\n")){
        loadTex(file, game, tmp);
        fgets(type, 10, file);
    }

    children = children->next;
    tmp = children->child;
    // Import ui
    while(strcmp(type, "END\n")){
        loadTex(file, game, tmp);
        fgets(type, 10, file);
    }
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
