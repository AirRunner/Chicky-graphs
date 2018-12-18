#ifndef DATA_H
#define DATA_H

#include <string.h>

#include "../controller/graphs.h"


typedef struct textSLL {
    char* text;
    struct textSLL* next;
} TextSLL;

char* missionToStr(MissionNumber nbMission);
MissionNumber strToMission(char *str);

int missionSucceeded(Game* game);
int checkMission5_6(Game* game);

void loadMission(Game* game);
char* pathMission(MissionNumber Nbmission);

void NodesMissions(FILE* fichier, Game* game, int size);
void EdgesMissions(FILE* fichier, Game* game, int size);
void UIMissions(FILE* fichier, Game* game, int size);

TextSLL* newTextNode(char* r);
void addTextNode(TextSLL** pt, char* r);
void removeTextNode(TextSLL** textSLL);
void freeTextSLL(TextSLL** textSLL);
void printTextSLL(TextSLL* Text);

void readFile(const char* mission, Game* game);

//void DisplayText(Listext *Text);

#endif
