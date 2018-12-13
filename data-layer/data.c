#include <string.h>
#include "data.h"

void NbMission(Game *game){
	int j =0;
	char *MisB = malloc(sizeof(char)*1000);
	//for (nB = Menu; nB < Mission1; nB++){
		MisB = numbermission(*game->missionNumber);
		j ++;
		readFile(MisB, game);
		//mettre la suite
	//}
}

char* numbermission( MissionNumber Themission){
	char* mission = malloc(sizeof(char)*1000);
	if (Themission == Menu){
		return("../data/missions/Menu.txt");
	}
	else{
		sprintf(mission, "../data/missions/Mission%d.txt", Themission);
		return(mission);
	}
}

void NodesMissions(FILE *fichier, Game * game, long size){
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
}

void EdgesMissions(FILE *fichier, Game * game, long size){
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
	
}


List* AddText(List* Text, char* readT) {
	List *current_Text = Text;
	List *newText;
	newText = (List *) malloc(sizeof(List));
	newText->readText = readT;
	newText->nexText= NULL;
	while ( current_Text != NULL && current_Text->nexText != NULL) {
		//ici problème 
		current_Text = current_Text->nexText;
	}
	if (current_Text != NULL)
		current_Text->nexText = newText;
	else
		Text = newText;
	return Text;
}

void print(List *Text) {
	List *current_text = Text;
	while ( current_text != NULL) {
		printf("\n%s\n ", current_text->readText);
		current_text = current_text->nexText;
	}
}


void UIMissions(FILE *fichier, Game * game, long size){
	int q,p,x,y,w,h;
	char *lign = malloc(sizeof(char)*1000);
	char *test = malloc(sizeof(char)*1000);
	char *texture = malloc(sizeof(char)*1000);
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
		addUI(&game->renderingSLL->ui, createRect(x, y, w, h), searchTex(game->texTree, "UI", texture), button);
	}
	fgets(lign,size,fichier);
	fgets(lign,size,fichier);
	sscanf(lign,"%s", test);
	if (strcmp(test, "-Text-") == 0){
			List* TEXT = NULL;
			fgets(lign,size,fichier);
			p = atoi(lign);
			while(fgets(lign,size,fichier) != NULL){
				sscanf(lign,"%s", test);
				if (strcmp("***", test) == 0){
					fgets(lign,size,fichier);
					TEXT = AddText(TEXT, lign);	
				}
			}
				FC_Font* font = FC_CreateFont();
				FC_LoadFont(font, game->renderer, "../data/fonts/NotoSansMono-Regular.ttf", 18, FC_MakeColor(0,0,0,255), TTF_STYLE_NORMAL);
				game->text = createText(TEXT->readText, font, 400, 600, 800, 800);
	}
}



void readFile(const char* mission, Game* game){
	FILE * fichier = NULL;
	char *lign = malloc(sizeof(char)*1000);
	char *test = malloc(sizeof(char)*1000);
	long size;
	fichier = fopen(mission, "r");
	if (fichier != NULL){
		// pointer points to the end to get the size
		fseek(fichier, 0L, SEEK_END);
		size = ftell(fichier);
		// pointer points to the beginning of the file
		fseek(fichier, 0L, SEEK_SET);
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
