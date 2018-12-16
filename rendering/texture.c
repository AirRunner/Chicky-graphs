#include "texture.h"
#include "../controller/graphs.h"

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

EltTree* addChild(NodeTree* parent, char* name, SDL_Texture* texture)
{
    NodeTree* newNodeTree = createNodeTree(name, texture);
    EltTree* newChild = createEltTree(newNodeTree);

    if(parent->children == NULL)
    {
        parent->children = newChild;
        return newChild;
    }
    else
    {
        EltTree* tmp = parent->children;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newChild;
        return newChild;
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
void loadTex(FILE* file, Game* game, NodeTree* texTree, char* type){
    char* name = malloc(50 * sizeof(char));
    char* tex = malloc(100 * sizeof(char));
    fgets(name, 50, file); name[strlen(name)-1] = '\0';
    fgets(tex, 100, file); tex[strlen(tex)-1] = '\0';
    // Search the good type
    EltTree* children = texTree->children;
    while(children && strcmp(children->child->name, type)){
        children = children->next;
    }
    // Create the type if it doesn't already exist
    if(!children){
        char* typeName = malloc(10 * sizeof(char));
        strcpy(typeName, type);
        children = addChild(texTree, typeName, NULL);
    }
    // Add the texture in the good type branch
    addChild(children->child, name, createTex(game, tex));
}

void initTex(Game* game)
{
    // Load file containing assets' type, name and path
    FILE* file = NULL;
    file = fopen("../data/Assets/importTextures.txt","r");
    char* type = malloc(10 * sizeof(char));

    game->texTree = createNodeTree("Textures", NULL);

    // Import textures
    while(fgets(type, 10, file)){
        type[strlen(type)-1] = '\0';
        loadTex(file, game, game->texTree, type);
    }
    // Set background
    game->background = createUI(createRect(0, 0, 1280, 720), searchTex(game->texTree, "UI", "Background"), background);

    free(type);
    fclose(file);
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
    // Search the good type (edge, node or UI)
    while(children != NULL && strcmp(children->child->name, type)){
        children = children->next;
    }
    if(children == NULL){
        printf("Type not found: %s\n", type);
        return NULL;
    }
    children = children->child->children;
    // Search the good texture
    while(children != NULL && strcmp(children->child->name, name)){
        children = children->next;
    }
    if(children == NULL){
        printf("Texture not found: %s\n", name);
        return NULL;
    }
    return children->child->texture;
}

SDL_Texture* textureRect(Game* game, SDL_Rect* rect){
    return game->graph->array[searchNode(game->graph, rect)]->nodeSDL->tex;
}

char* nextTex(NodeTree* textures, SDL_Texture* currTex) {
    EltTree* children = textures->children->child->children;
    while (children != NULL && children->child->texture != currTex) {
        children = children->next;
    }
    children = children->next;
    // End of basic textures
    if (children == NULL || strstr(children->next->child->name, "Infected") != NULL) {
        return NULL;
    }
    return children->child->name;
}
