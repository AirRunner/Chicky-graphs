#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_fill_ALL.h"


void numbermission(char* mis, char* nber){
	char* mission = malloc(sizeof(char)*1000);
	strcpy(mission, "../data/missions/");
	strcat(mission,mis);
	strcat(mission,nber);
	strcat(mission,".txt");
	readFile(mission);
}

void readFile(const char* mission){
	FILE * fichier = NULL;
	char *lign = malloc(sizeof(char)*1000);
	char *test = malloc(sizeof(char)*1000);
	char *texture= malloc(sizeof(char)*1000);
	char *token;
	long size;
	int x,y,w,h,d,node,directed,j,k,i,m,n,p,q;
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
			if (strcmp(test, "-------Nodes-----") == 0){
				printf("\n%s\n", test);
				j = 0;
				fgets(lign, size, fichier);
				printf("Texture : %s\n",lign);
				texture = lign; 
				fgets(lign, size, fichier);
				node = atoi(lign);
				fgets(lign, size, fichier);
				directed = atoi(lign);
				if (directed == 0 || directed == 1){
					printf("Directed:%d\nNodes :%d\n", directed, node);
				}
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
					printf("\nNode :\nd-->%d \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n", d,x,y,w,h);
					//createNode(game->graph, d, &game->renderingSLL->nodes, createRect(x, y, w, h), searchTex(game->texTree, "Node", texture));
				}
				sscanf(lign, "%s", test);
			}
			if (strcmp(test, "-------Edges------") == 0){
				printf("\n%s\n", test);
				fgets(lign, size, fichier);
				i = atoi(lign);
				k = 0;
				printf("Number of edges : %d\n", i);
				fgets(lign, size, fichier);
				if (i != 0){
					while (k != i){
						fgets(lign,size,fichier);
						token =   strtok(lign, "-");
						m = atoi(lign);
						token = strtok(NULL, "-");
						n = atoi(lign);
						token = strtok(NULL,"-");
						printf("Source: %d Destinataire: %d\n", m,n);
						k++;
						//addEdge( game->graph,  m,  n,  1,  &game->renderingSLL->edges, NULL);
					}
				}
				sscanf(lign, "%s", test);
			}

			if (strcmp(test, "---------UI--------") == 0){
				printf("\n%s\n", test);
				fgets(lign,size,fichier);
				q = atoi(lign);
				for (p=0; p <q;p++){
					fgets(lign,size,fichier);
					fgets(lign,size,fichier);
					printf("\nTexture : %s\n", lign);
					// fonction /type
					fgets(lign,size,fichier);
					x = atoi(lign);
					fgets(lign,size,fichier);
					y = atoi(lign);
					fgets(lign,size,fichier);
					w = atoi(lign);
					fgets(lign,size,fichier);
					h = atoi(lign);
					printf("\ncoordonnées : \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n",x,y,w,h);
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
							printf("text:  \n\n %s", lign);
						}
					}
				}

			}
		}
	}
	fclose(fichier);
	free(lign);
	//free(test);
}



int main() {
	printf("The menu: \n");
	numbermission("Mission","3");
	//readFile("../data/missions/Menu.txt");

	return(0);
}