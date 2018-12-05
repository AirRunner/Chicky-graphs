#ifndef DATA_H
#define DATA_H

#include "data.h"

#include "../controller/graphs.h"

void NodesMissions(FILE *fichier, Game * game, long size);

void EdgesMissions(FILE *fichier, Game * game, long size);

void UIMissions(FILE *fichier, Game * game, long size);

char* numbermission(char* mis, char* nber, Game* game);

void readFile(const char* mission, Game* game);

#endif
