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
	int j,node, directed,x,y,w,h,d;
	j = 0;
	fgets(lign, size, fichier);
	node = atoi(lign);
	fgets(lign, size, fichier);
	directed = atoi(lign);
	game->graph = createGraph(node, directed);
	while (j != node){
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
		LisText* Text = malloc(sizeof(LisText));
		LisText* tmp;
		fgets(lign,size,fichier);
		p = atoi(lign);
		for (q=0; q <p;q++){
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			if (strcmp("***", test) == 0){
				fgets(lign,size,fichier);
				if (q == 0){
					Text->readText = lign;
					Text->nexText = malloc(sizeof(char)*1000);
					tmp = Text;
					tmp = tmp->nexText;
					}
				else {
					tmp->readText = lign;
					tmp->nexText = malloc(sizeof(char)*1000);
					tmp = tmp->nexText;
				}
			}
		}
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
