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

typedef enum MissionNumber{
	Menu,
    Mission1,
    Mission2,
    Mission3,
    Mission4,
    Mission5,
    Mission6,
    Mission7,
    Mission8,
    Mission9,
    Mission10,
    Mission11,
    Mission12,
}MissionNumber;

void NbMission(Game *game);

char* numbermission(MissionNumber Nbmission);

void NodesMissions(FILE *fichier, Game * game, long size);

void EdgesMissions(FILE *fichier, Game * game, long size);

void UIMissions(FILE *fichier, Game * game, long size);

void readFile(const char* mission, Game* game);

//void DisplayText(Listext *Text);

#endif
