#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../controller/graphs.h"

typedef struct Node_mission{
	char texture;
	int x;
	int y;
	int w;
	int h;
	//struct Node* node;
}N_ode;


typedef struct Edge_mission{
	int src;	//chemin de N1_data à N2_data 
	//struct Edge* edge;
}E_dges;


typedef struct Graph_mission{
	int directed;
	int size;
}Graph_mis;
//se focaliser que sur Nodes et Edges pour l'instant

void readFile(const char* mission){
	FILE * fichier = NULL;
	char *lign = (char*)malloc(sizeof(char));
	char *test = (char*)malloc(sizeof(char));
	long size; 
	int node, directed;
	int j = 0; 
	fichier = fopen(mission, "r");
	if (fichier != NULL){
		// pointer points to the end to get the size 
		fseek(fichier, 0L, SEEK_END);
		size = ftell(fichier);
		// pointer points to the beginning of the file
		fseek(fichier, 0L, SEEK_SET);
		while (fgets(lign,size,fichier) != NULL){
				//reads formatted input from a string
				sscanf(lign, "%s", test);
				//Je vais essayer de l'optimiser mais pour l'instant fonctionnne pour les NODES 
				if (strcmp(test, "-------Nodes------") == 0){
					int x,y,w,h,d;
					printf("\n%s\n", test);	
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					node = atoi(test);
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					directed = atoi(test);
					if (directed == 0 || directed == 1){
						printf("FONCTIONS VICTOR");
						//Graph_mis * graph = (Graph_mis*)malloc(sizeof(Graph_mis));
						//graph->directed = directed;
						//graph->size = node;
						//put fonction de Victor ::: Graph* graph = createGraph(node, directed);
					}
					while (j != node){
						j++;
						fgets(lign, size, fichier);
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						x = atoi(test);
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						y = atoi(test);
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						w = atoi(test);
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						h = atoi(test);
						printf("\nNode :%d \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n", j,x,y,w,h);	
						
						// function ==> Vincent test	
						printf("Fonction de Victor/ Vincent ICI");
						//fonction de Victor récupérer les infos sur chaque node
						// j : numéro du node = data 
						// x / y / w / h pour Vincent 				
					}
				}
				if (strcmp(test, "-------Edges-------") == 0){
					printf("\n%s\n", test);
					//function Edges
				}
				if (strcmp(test, "---------UI---------") == 0){
					printf("\n%s\n", test);
					//function UI
				}
		}
	}
	fclose(fichier);
}


	

int main() {
	
	readFile("../data/missions/Mission3.txt");
	
	
	return(0);
}


/*
SEEK_CUR
	
	
if (strcmp(test, "-------Nodes------") == 0){
	printf("%s", test);
	SEEK_CUR : on balaye le fichier une première fois
	fgets(lign,size,fichier);
convert string into integer
	nodes = atoi(lign);
	for ( i = 0; i<nodes ; i++){
	fgets(lign,size,fichier);
	}
	
void Missions(){
		
	char* Mission_10 =ReadOnFileMission("IDEE.txt");
	printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_10);
}


size =  printf("%lu", sizeof(buffer)); 

char *ReadOnFileMission(const char *name){
	char* buffer;
	FILE *fichier = NULL;
	long    number;
	fichier = fopen(name,"r");

	if (fichier != NULL){
		fseek(fichier, 0L, SEEK_END);
		number = ftell(fichier);
		fseek(fichier, 0L, SEEK_SET);
		buffer = (char*)calloc(number, sizeof(char));	
		fread(buffer, sizeof(char), number, fichier);
		}
	fclose(fichier);
	//printf("The file  contains this text\n\n%s", buffer);
	return(buffer);	
}
	while (node){
			do {
				fgets(lign,size,fichier);
				sscanf(lign,"%s", test);
			}while (test == NULL);
			printf("TEST");
			
		}
		
		do{
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			x = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			y = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			w = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			h = atoi(test);
			printf("%d\n  %d\n  %d\n  %d\n", x,y,w,h);
			
		}while (strcmp(test, "-----") != 0);

		
		
		fgets(lign,size,fichier);
		sscanf(lign,"%s", test);
		
		if ( strcmp(res,"N") == 0){
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			x = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			y = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			w = atoi(test);
			fgets(lign,size,fichier);
			sscanf(lign,"%s", test);
			h = atoi(test);
				//createNodeSDL
				//createNode( graph, k, NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex)
		}*/
