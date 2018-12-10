#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

#include "../controller/graphs.h"

typedef enum MissioNumber MissioNumber;

typedef struct LisText{
	char *readText;
	struct LisText* nexText;
}LisText;

enum  MissioNumber{
	Menu, Mission1, Mission2, Mission3, Mission4, Mission5, Mission6, Mission7, Mission8, Mission9,Mission10, Mission11, Mission12,
};

void NbMission(Game *game);

char* numbermission(MissioNumber Nbmission);

void NodesMissions(FILE *fichier, Game * game, long size);

void EdgesMissions(FILE *fichier, Game * game, long size);

void UIMissions(FILE *fichier, Game * game, long size);

void readFile(const char* mission, Game* game);

//void DisplayText(Listext *Text);

#endif
