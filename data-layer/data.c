#include "data.h"
#include "../rendering/text.h"

struct conversion
{
    UIType val;
    char *str;
} conversion[] = { //directly making the table
    {next, "next"},
    {menu, "menu"},
    {sandbox, "sandbox"},
    {newGame, "newGame"},
    {resumeGame, "resumeGame"},
    {background, "background"},
    {other, "other"}
};

UIType strToEnum(char *str)
{
     int i;
     for(i = 0; i < sizeof(conversion)/sizeof(conversion[0]); ++i) //works for all types
     {
         if(!strcmp(str, conversion[i].str))
         {
             return conversion[i].val;
         }
     }
     printf("convertion failed, returning other\n");
     return other;
}

struct convMissions
{
    MissionNumber val;
    char *str;
} convMissions[] = { // Conversion table between missions enum and str
    {Menu, "Menu"},
    {Mission1, "Mission1"},
    {Mission2, "Mission2"},
    {Mission3, "Mission3"},
    {Mission4, "Mission4"},
    {Mission5, "Mission5"},
    {Mission6, "Mission6"},
    {Mission7, "Mission7"},
    {Mission8, "Mission8"},
    {Mission9, "Mission9"},
    {Mission10, "Mission10"},
    {Mission11, "Mission11"},
    {Mission12, "Mission12"}
};

char* missionToStr(MissionNumber nbMission)
{
     int i;
     for(i = 0; i < sizeof(convMissions)/sizeof(convMissions[0]); ++i)
     {
         if(nbMission == convMissions[i].val)
         {
             return convMissions[i].str;
         }
     }
     printf("convertion failed, returning other\n");
     return "Menu";
}

MissionNumber strToMission(char *str)
{
     int i;
     for(i = 0; i < sizeof(convMissions)/sizeof(convMissions[0]); ++i)
     {
         if(!strcmp(str, convMissions[i].str))
         {
             return convMissions[i].val;
         }
     }
     printf("convertion failed, returning other\n");
     return Menu;
}

int missionSucceeded(Game* game){
    if(game->missionNumber == Mission3){
        if(!(game->graph->array[0]->node->list && game->graph->array[0]->node->list->dest == 1)){
            return 0;
        }
    }
    return 1;
}

void loadMission(Game *game){
	readFile(pathMission(game->missionNumber), game);
}

char* pathMission(MissionNumber Themission){
	char* mission = malloc(sizeof(char)*100);
	if (Themission == Menu){
		return "../data/missions/Menu.txt";
	}
    else if(Themission == Sandbox){
        return "../data/missions/Sandbox.txt";
    }
	else{
		sprintf(mission, "../data/missions/Mission%d.txt", Themission);
		return mission;
	}
}

void NodesMissions(FILE *fichier, Game * game, int size){
	char *lign = malloc(sizeof(char)*1000);
	char *texture = malloc(sizeof(char)*50);
	int j,node, directed, count, x,y,w,h,d;
	j = 0;
	fgets(lign, size, fichier);
	node = atoi(lign);
	fgets(lign, size, fichier);
	directed = atoi(lign);
	fgets(lign,size,fichier);
	count = atoi(lign);
	game->graph = createGraph(node, directed);
	while (j != count){
		j++;
		fgets(lign, size, fichier);
		fgets(lign,size,fichier);
		lign[strlen(lign)-1] = '\0';
		strcpy(texture,lign);
		fgets(lign,size,fichier);
		x = atoi(lign);
		fgets(lign,size,fichier);
		y = atoi(lign);
		fgets(lign,size,fichier);
		w = atoi(lign);
		fgets(lign,size,fichier);
		h = atoi(lign);
		fgets(lign,size,fichier);
		d = atoi(lign);
		createNode(game->graph, d, &game->renderingSLL->nodes, createRect(x, y, w, h), searchTex(game->texTree, "Node", texture));
	}
	free(lign);
	free(texture);
}

void EdgesMissions(FILE *fichier, Game * game, int size){
	int i, k, m,n;
	char* lign = malloc(sizeof(char)*1000);
	char* token = NULL;
	fgets(lign, size, fichier);
	i = atoi(lign);
	k = 0;
	fgets(lign, size, fichier);
	if (i){
		while (k != i){
			fgets(lign,size,fichier);
			token = strtok(lign, "-");
			m = atoi(token);
			token = strtok(NULL, "-");
			n = atoi(token);
			token = strtok(NULL,"-");
			k++;
			addEdge( game->graph,  m-1,  n-1,  1,  &game->renderingSLL->edges, NULL);
		}
	}
	free(lign);
    free(token);
}

TextSLL* newTextNode(char* text) {
		TextSLL* t = malloc(sizeof(TextSLL));
		t->text = text;
		t->next= NULL;
		return t;
}

void addTextNode(TextSLL** textSLL, char* text){
    char* tmp = malloc(sizeof(char)*1000);
    strcpy(tmp, text);
	if (!*textSLL){
		*textSLL = newTextNode(tmp);
	}
	else {
		addTextNode(&(*textSLL)->next, text);
	}
}

void removeTextNode(TextSLL** textSLL){
    if(*textSLL)
    {
        TextSLL* tmp = *textSLL;
        *textSLL = (*textSLL)->next;
        free(tmp->text);
        free(tmp);
    }
}

void freeTextSLL(TextSLL** textSLL){
    if(textSLL)
    {
        while(*textSLL)
        {
            removeTextNode(textSLL);
        }
    }
}

void printTextSLL(TextSLL* text) {
	if (text != NULL){
		TextSLL* currentText = text;
		while ( currentText != NULL) {
            printf("%s", text->text);
			currentText = currentText->next;
		}
	}
}


void UIMissions(FILE* fichier, Game* game, int size){
	int q,p,x,y,w,h;
	char *lign = malloc(sizeof(char)*1000);
	char *texture = malloc(sizeof(char)*1000);
	fgets(lign,size,fichier);
	q = atoi(lign);
	for (p=0; p <q;p++){
		fgets(lign,size,fichier);
		fgets(lign,size,fichier);
		lign[strlen(lign)-1] = '\0';
		strcpy(texture,lign);
		fgets(lign,size,fichier);
		x = atoi(lign);
		fgets(lign,size,fichier);
		y = atoi(lign);
		fgets(lign,size,fichier);
		w = atoi(lign);
		fgets(lign,size,fichier);
		h = atoi(lign);
		printf("%d,%d,%d,%d\n", x,y,w,h);
        fgets(lign,size,fichier);
        lign[strcspn(lign, "\n")] = '\0'; //exchanges the \n for a \0
		addUI(&game->renderingSLL->ui, createRect(x, y, w, h), searchTex(game->texTree, "UI", texture), strToEnum(lign));
	}
	fgets(lign,size,fichier);
	fgets(lign,size,fichier);
    lign[strcspn(lign, "\n")] = '\0';
	if (!strcmp(lign, "-Text-")){
			fgets(lign,size,fichier);
			TextSLL* text = NULL;
			p = atoi(lign);
			for (q = 0; q < p; q++){
				fgets(lign,size,fichier);
				fgets(lign,size,fichier);
				printf("%s\n", lign);
				addTextNode(&text, lign);
			}
            freeTextSLL(&game->text->textSLL);
            game->text->textSLL = text;
	}
    free(lign);
    free(texture);
}



void readFile(const char* mission, Game* game){
	FILE * fichier = NULL;
	char *lign = malloc(sizeof(char)*1000);
	int size = 1000;
	fichier = fopen(mission, "r");
	if (fichier != NULL){
		while (fgets(lign,size,fichier)){
			//reads formatted input from a string
            lign[strcspn(lign, "\n")] = '\0';
			if (strcmp(lign, "-------Nodes-----") == 0){
				NodesMissions(fichier, game, size);
				fgets(lign, size, fichier);
                lign[strcspn(lign, "\n")] = '\0';
			}
			if (strcmp(lign, "-------Edges------") == 0){
				EdgesMissions(fichier, game, size);
				fgets(lign, size, fichier);
                lign[strcspn(lign, "\n")] = '\0';
			}
			if (strcmp(lign, "---------UI--------") == 0){
				UIMissions(fichier, game, size);
				fgets(lign, size, fichier);
                lign[strcspn(lign, "\n")] = '\0';
			}
		}
	}
	fclose(fichier);
	free(lign);
}
