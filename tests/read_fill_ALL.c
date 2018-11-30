#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char* mission){
	FILE * fichier = NULL;
	char *lign = (char*)malloc(sizeof(char));
	char *test = (char*)malloc(sizeof(char));
	long size; 
	int x,y,w,h; 
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
					int x,y,w,h,d,node,directed,j;
					j = 0;
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					printf("Texture : %s\n",test);
					//Fonction de Victor pour les textures
					
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					node = atoi(test);
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					directed = atoi(test);
					if (directed == 0 || directed == 1){
						printf("Directed/undirected \n");
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
						printf("\nNode :%d \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n", d,x,y,w,h);
//createNode(Graph* graph, int data, NodeSDL** nodes, SDL_Rect* destRect, SDL_Texture* tex);		
						// x / y / w / h pour Vincent 	+ 1 data 0 contamined
					}
				}
				if (strcmp(test, "-------Edges------") == 0){
					printf("\n%s\n", test);	
					char* token;
					fgets(lign, size, fichier);
					sscanf(lign,"%s", test);
					int k,i,m,n;
					i = atoi(test);
					k = 0;
					printf("Number of edges : %d", i);
					fgets(lign, size, fichier);
					if (i != 0){
						while (k != i){
							fgets(lign,size,fichier);
							sscanf(lign,"%s", test);
							token =   strtok(test, "-");
							m = atoi(test);
							printf( "Source: %s\n", token );
							token = strtok(NULL, "-");
							n = atoi(test);
							printf( "Destinataire: %s\n", token );
							token = strtok(NULL,"-");
							k++;
							//addEdge( graph,  m,  n,  1, edges, texArrow)  
						}
					}
				}
				
				if (strcmp(test, "---------UI--------") == 0){
					int x,y,w,h,p;
					printf("\n%s\n", test);	
					for (p=0; p <2;p++){
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
						char *textlire= (char*)malloc(sizeof(char));
						char *toke;
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
								toke = strtok(test, "_");
								strcpy(textlire, "");
								while( toke != NULL ) {
									strcat(textlire, toke);
									toke = strtok(NULL, "_");
									strcat(textlire," ");
									}					
									//ici save le texte
								printf("\n%s\n", textlire);
								
							}
						} 
						
					}
					
			}
		}
	}
	fclose(fichier);
}


	

int main() {
	
	readFile("../data/missions/Mission3.txt");
	
	
	return(0);
}