#include <stdio.h>
#include <stdlib.h>

//Implementation of a tree with multuple childrens

typedef struct elt
{
    struct node* child;
    struct elt* next;
}Elt;

typedef struct node
{
    int data;
    struct elt* children;
}Node;

Elt* createElt(Node* child)
{
    Elt* newElt = (Elt*) malloc(sizeof(Elt));
    newElt->child = child;
    newElt->next = NULL;
    return newElt;
}

Elt* freeSLL(Elt* children)
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

Node* createNode(int data)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->children = NULL;
    return newNode;
}

void addChild(Node* parent, int data)
{
    Node* newNode = createNode(data);
    Elt* newChild = createElt(newNode);

    if(parent->children == NULL)
    {
        parent->children = newChild;
    }
    else
    {
        Elt* tmp = parent->children;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newChild;
    }
}

//Elt* deleteAllOccurences(Elt* children, int data)
//{
//    if(children == NULL)
//    {
//        return NULL;
//    }
//    else if(children->child->data != data)
//    {
//        children->next = deleteAllOccurences(children->next);
//        return children;
//    }
//    else
//    {
//        if(children->next != NULL)
//        {
//            children->next->next = deleteAllOccurences(children->next->next);
//        }
//        
//
//        return children->next;
//    }
//}

//Elt* deleteAllChildren(Elt* children)
//{
//    if(children == NULL)
//    {
//        return NULL;
//    }
//    if(children->next = NULL)
//    {
//        children->child->children = deleteAllChildren(children->child->children);
//        free(children->child);
//        free(children);
//        return NULL;
//    }
//    else
//    {
//        children->next = deleteAllChildren(children->next);
//        children->child->children = deleteAllChildren(children->child->children);
//        free(children->child);
//        free(children);
//        return NULL;
//    }
//}
//
//void deleteNode(Node* node)
//{
//    node->children = deleteAllChildren(node->children);
//    free(node);
//}

Node* freeTree(Node* node)
{
    if(node->children == NULL)
    {
        free(node);
        return NULL;
    }
    else
    {
        Elt* tmp = node->children;
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

Elt* deleteChildIndex(Elt* children, int index) //SLL begins at 0
{
    if(index < 0)
    {
        return children;
    }
    else if(index == 0)
    {
        children->child = freeTree(children->child);
        Elt* tmp = children->next;
        free(children);
        return tmp;
    }
    else
    {
        children->next = deleteChildIndex(children->next, index-1);
        return children;
    }
}

Elt* deleteChildFO(Elt* children, int data) //FO = First Occurence
{
    if(children == NULL)
    {
        return NULL;
    }
    else if(children->child->data == data)
    {
        children->child = freeTree(children->child);
        Elt* tmp = children->next;
        free(children);
        return tmp;
    }
    else
    {
        children->next = deleteChildFO(children->next, data);
        return children;
    }
}

Elt* deleteChildAO(Elt* children, int data) //AO = ALL Occurence
{
    if(children == NULL)
    {
        return NULL;
    }
    else if(children->child->data == data)
    {
        children->child = freeTree(children->child);
        Elt* tmp = children->next;
        free(children);
        tmp->next = deleteChildAO(tmp->next, data);
        return tmp;
    }
    else
    {
        children->next = deleteChildAO(children->next, data);
        return children;
    }
}

void printTreePrefixe(Node* root)
{
    if(root != NULL)
    {
        printf("%d\n", root->data);
        Elt* tmp = root->children;
        while(tmp != NULL)
        {
            printTreePrefixe(tmp->child);
            tmp = tmp->next;
        }
    }
}

void test()
{
    Node* root = createNode(0);
    for(int i = 1; i < 10; ++i)
        addChild(root, i);
    Elt* tmp = root->children;
    while(tmp != NULL)
    {
        for(int i = 0; i < 10; ++i)
        {
            addChild(tmp->child, i+10*tmp->child->data);
        }
        tmp = tmp->next;
    }
    printTreePrefixe(root);
    root->children = deleteChildFO(root->children, 1);
    printf("\n");
    printTreePrefixe(root);
    root->children = deleteChildIndex(root->children, 1);
    printf("\n");
    printTreePrefixe(root);
    root = freeTree(root);
    printf("\n");
    printTreePrefixe(root);
}

int main()
{
    test();
    return 0;
}
