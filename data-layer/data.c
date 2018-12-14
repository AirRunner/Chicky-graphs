#include <string.h>
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

void loadMission(Game *game){
	readFile(pathMission(game->missionNumber), game);
}

char* pathMission(MissionNumber Themission){
	char* mission = malloc(sizeof(char)*100);
	if (Themission == Menu){
		return "../data/missions/Menu.txt";
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
	char *lign = malloc(sizeof(char)*1000);
	char* token;
	fgets(lign, size, fichier);
	i = atoi(lign);
	k = 0;
	fgets(lign, size, fichier);
	if (i != 0){
		while (k != i){
			fgets(lign,size,fichier);
			token =   strtok(lign, "-");
			m = atoi(token);
			token = strtok(NULL, "-");
			n = atoi(token);
			token = strtok(NULL,"-");
			k++;
			addEdge( game->graph,  m-1,  n-1,  1,  &game->renderingSLL->edges, NULL);
		}
	}
	free(lign);
}

TextSLL* newTextNode(char* text) {
		TextSLL* t = malloc(sizeof(TextSLL));
		t->text = text;
		t->next= NULL;
		return t;
}

void AddTextNode(TextSLL** textSLL, char* text){
	if (!*textSLL){
		printf("\nENTRER ICI\n");
		*textSLL = newTextNode(text);
	}
	else {
		printf("\nENTRER LA\n");
		AddTextNode(&(*textSLL)->next, text);
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
	char *test = malloc(sizeof(char)*1000);
	char *texture = malloc(sizeof(char)*1000);
	char *type = malloc(sizeof(char)*1000);
	fgets(lign,size,fichier);
	q = atoi(lign);
	for (p=0; p <q;p++){
		fgets(lign,size,fichier);
		fgets(lign,size,fichier);
		lign[strlen(lign)-1] = '\0';
		strcpy(texture,lign);
		//printf("\nTexture : %s\n", lign);
		// fonction /type
		fgets(lign,size,fichier);
		x = atoi(lign);
		fgets(lign,size,fichier);
		y = atoi(lign);
		fgets(lign,size,fichier);
		w = atoi(lign);
		fgets(lign,size,fichier);
		h = atoi(lign);
		printf("%d,%d,%d,%d\n", x,y,w,h);
        fgets(type,size,fichier);
        type[strcspn(type, "\n")] = '\0'; //exchanges the \n for a \0
        printf("type: %s\n", type);
		addUI(&game->renderingSLL->ui, createRect(x, y, w, h), searchTex(game->texTree, "UI", texture), strToEnum(type));
	}
	fgets(lign,size,fichier);
	fgets(lign,size,fichier);
	sscanf(lign,"%s", test);
	if (strcmp(test, "-Text-") == 0){
			fgets(lign,size,fichier);
			TextSLL* text = NULL;
			p = atoi(lign);
			for (q = 0; q < p; q++){
				fgets(lign,size,fichier);
				fgets(lign,size,fichier);
				printf("%s\n", lign);
				AddTextNode(&text, lign);
			}
            if(!game->text)
            {
                printTextSLL(text);
                FC_Font* font = FC_CreateFont();
                FC_LoadFont(font, game->renderer, "../data/fonts/NotoSansMono-Regular.ttf", 18, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
                // Text[d]

                game->text = createText(text, font, 400, 600, 600, 800);
            }
            else
            {
                //freeTextSLL(game->text->textSLL);
                game->text->textSLL = text;
            }
	}

}



void readFile(const char* mission, Game* game){
	FILE * fichier = NULL;
	char *lign = malloc(sizeof(char)*1000);
	char *test = malloc(sizeof(char)*1000);
	int size = 1000;
	fichier = fopen(mission, "r");
	if (fichier != NULL){
		while (fgets(lign,size,fichier) != NULL){
			//reads formatted input from a string
			sscanf(lign,"%s", test);
			if (strcmp(test, "-------Nodes-----") == 0){
				NodesMissions(fichier, game, size);
				fgets(lign, size, fichier);
				sscanf(lign, "%s", test);
			}
			if (strcmp(test, "-------Edges------") == 0){
				EdgesMissions(fichier, game, size);
				fgets(lign, size, fichier);
				sscanf(lign, "%s", test);
			}
			if (strcmp(test, "---------UI--------") == 0){
				UIMissions(fichier, game, size);
				fgets(lign, size, fichier);
				sscanf(lign, "%s", test);
			}
		}
	}
	fclose(fichier);
	free(lign);
	free(test);
}



	/*

	void AddText(Txt *pt, char* r){
		if ((*pt) == NULL)
			(*pt) = new_node(r);
		else {
			AddText(&(*pt)->nexText, r);
		}
	}

	Txt AddText(Txt Text, char* readT) {
		Txt current_Text = Text;
		Txt newText;
		newText = new_node(readT);
		while ( current_Text != NULL && current_Text->nexText != NULL) {
			//ici problème
			current_Text = current_Text->nexText;
		}
		if (current_Text != NULL)
			current_Text->nexText = newText;
		else
			Text = newText;
		printf("ETAPE");
		print(Text);
		return Text;
	}
	Txt AddText(Txt pt, char* r){
		if ((pt) == NULL){
			(pt) = new_node(r);
		}
		else {
			Txt t = malloc(sizeof(List));
			t = pt;
			while (t != NULL){
				t = t->nexText;
			}
			printf("TEST");
			print(t);
		//	Txt t = malloc(sizeof(List));
		//	t = pt;
		//	while ( t != NULL)
		//		t = t->nexText;
		//	t = new_node(r);
			//printf("%s", (*pt)->readText);
			//AddText(&(*pt)->nexText, r);
		}
		return(pt);
	}*/
