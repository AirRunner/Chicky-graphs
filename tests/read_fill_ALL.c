#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char* mission){
	FILE * fichier = NULL;
	char *lign = malloc(sizeof(char)*1000);
	char *test = malloc(sizeof(char)*1000);
	char *textlire= malloc(sizeof(char)*1000);
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
				sscanf(lign, "%s", test);
				printf("Texture : %s\n",test);
				//Fonction de Victor pour les textures ATTENTION EN METTRE DEUXIEME
				fgets(lign, size, fichier);
				sscanf(lign, "%s", test);
				node = atoi(test);
				fgets(lign, size, fichier);
				sscanf(lign, "%s", test);
				directed = atoi(test);
				if (directed == 0 || directed == 1){
					printf("Directed:%d\n", directed);
//Graph* graph = createGraph(node, directed);
				}
				while (j != node){
					//changer data mettre à 0
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
					fgets(lign,size,fichier);
					sscanf(lign,"%s", test);
					d = atoi(test);
					printf("\nNode :\nd-->%d \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n", d,x,y,w,h);
//createNode(Graph* graph, int data, NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex);
					// x / y / w / h pour Vincent 	+ 1 data 0 contamined
				}
			}
			if (strcmp(test, "-------Edges------") == 0){
				printf("\n%s\n", test);
				fgets(lign, size, fichier);
				sscanf(lign,"%s", test);
				i = atoi(test);
				k = 0;
				printf("Number of edges : %d\n", i);
				fgets(lign, size, fichier);
				if (i != 0){
					while (k != i){
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						token =   strtok(test, "-");
						m = atoi(test);
						token = strtok(NULL, "-");
						n = atoi(token);
						token = strtok(NULL,"-");
						printf("Source: %d Destinataire: %d\n", m,n);
						k++;
						//addEdge( graph,  m,  n,  1, edges, texArrow)
					}
				}
			}

			if (strcmp(test, "---------UI--------") == 0){
				printf("\n%s\n", test);
				fgets(lign,size,fichier);
				sscanf(lign,"%s", test);
				q = atoi(test);
				for (p=0; p <q;p++){
					fgets(lign,size,fichier);
					fgets(lign,size,fichier);
					sscanf(lign,"%s", test);
					printf("\nTexture : %s\n", test);
					// fonction /type
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
					printf("\ncoordonnées : \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n",x,y,w,h);
				}
				fgets(lign,size,fichier);
				fgets(lign,size,fichier);
				sscanf(lign,"%s", test);
				if (strcmp(test, "-Text-") == 0){
					int i,l;
					fgets(lign,size,fichier);
					sscanf(lign,"%s", test);
					i = atoi(test);
					for (l=0; l <i;l++){
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						if (strcmp("***", test) == 0){
							fgets(lign,size,fichier);
							sscanf(lign,"%s", test);
							token = strtok(test, "_");
							strcpy(textlire, "");
							while( token != NULL ) {
								strcat(textlire, token);
								token = strtok(NULL, "_");
								strcat(textlire," ");
							}
							printf("\n%s\n", textlire);
						}
					}
					free(textlire);
					free(token);
				}

			}
		}
	}
	fclose(fichier);
	free(lign);
	free(test);
}




int main() {
	printf("The menu: \n");
	readFile("../data/missions/Menu.txt");
	printf("The Intro Mission: \n");
	readFile("../data/missions/MissionINTRO.txt");
	printf("\n\nMission 1: \n");
	readFile("../data/missions/Mission1.txt");
	printf("\n\nMission 2: \n");
	readFile("../data/missions/Mission2.txt");
	printf("\n\nMission 3: \n");
	readFile("../data/missions/Mission3.txt");
	printf("\n\nMission 4: \n");
	readFile("../data/missions/Mission4.txt");
	printf("\n\nMission 5: \n");
	readFile("../data/missions/Mission5.txt");
	printf("\n\nMission 6: \n");
	readFile("../data/missions/Mission6.txt");
	printf("\n\nMission 7: \n");
	readFile("../data/missions/Mission7.txt");
	printf("\n\nMission 8: \n");
	readFile("../data/missions/Mission8.txt");
	printf("\n\nMission 9: \n");
	readFile("../data/missions/Mission9.txt");
	printf("\n\nMission Finale: \n");
	readFile("../data/missions/MissionFINAL.txt");
	printf("\n\nMission Finale: \n");
	readFile("../data/missions/TO_BE_CONTINUED.txt");

	return(0);
}