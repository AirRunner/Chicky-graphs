#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_fill_ALL.h"

void numbermission(char* mis, char* nber, Game* game){
	char* mission = malloc(sizeof(char)*1000);
	strcpy(mission, "../data/missions/");
	strcat(mission,mis);
	strcat(mission,nber);
	strcat(mission,".txt");
	readFile(mission, game);
}

char* textureMission(int data){
	if (data == 0){
		return("Basic chick");
	}
	else {
		if (data == 1){
			return("Infected chick 1");
		}
		else {
			if (data == 2){
				return("Happy chick");
			}
			else {
				return("Teacher chick 1");
			}
		}
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
	while (j != node){
		j++;
		fgets(lign, size, fichier);
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
		texture = textureMission(d);
		SDL_QueryTexture(searchTex(game->texTree, "Node", texture), NULL, NULL, &w, &h);
		createNode(game->graph, d, &game->renderingSLL->nodes, createRect(x/4, y/4, w/4, h/4), searchTex(game->texTree, "Node", texture));
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
		//fonction pour les boutons
	}
	fgets(lign,size,fichier);
	fgets(lign,size,fichier);
	sscanf(lign,"%s", test);
	if (strcmp(test, "-Text-") == 0){
		int i,l;
		fgets(lign,size,fichier);
		i = atoi(lign);
		for (l=0; l <i;l++){
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			if (strcmp("***", test) == 0){
				fgets(lign,size,fichier);
				//fonction pour les textes
			//	printf("text:  \n\n %s", lign);
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
	//free(test);
	printGraph(game->graph);
}



//lign[strlen(lign)-1] = '\0';
//strcpy(texture,lign);