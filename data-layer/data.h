#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rendering/text.h"
#include "../controller/graphs.h"


typedef struct list_T {
    char* readText;
    struct list_T *nexText;
} List;

typedef List *Txt;


void NbMission(Game *game);

char* numbermission(MissionNumber Nbmission);

void NodesMissions(FILE *fichier, Game * game, long size);

void EdgesMissions(FILE *fichier, Game * game, long size);

void UIMissions(FILE *fichier, Game * game, long size);

Txt new_node(char* r);

void AddText(Txt* pt, char* r);

void print(Txt Text);

void readFile(const char* mission, Game* game);

//void DisplayText(Listext *Text);

#endif
