#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char* mission){
	FILE * fichier = NULL;
	char *lign = (char*)malloc(sizeof(char));
	char *test = (char*)malloc(sizeof(char));
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
				sscanf(lign, "%s", test);
				//Je vais essayer de l'optimiser mais pour l'instant fonctionnne pour les NODES 
				if (strcmp(test, "-------Nodes-----") == 0){
					printf("\n%s\n", test);	
					int x,y,w,h,d,node,directed,j;
					j = 0;
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					//Fonction de Victor pour les textures
					
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					node = atoi(test);
					fgets(lign, size, fichier);
					sscanf(lign, "%s", test);
					directed = atoi(test);
					if (directed == 0 || directed == 1){
						printf("Directed/undirected \n");
						//put fonction de Victor ::: Graph* graph = createGraph(node, directed);
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
						printf("\nNode :%d \nx-->%d\ny-->%d\nw-->%d\nh-->%d\n\n", j,x,y,w,h);	
						
						// function ==> Vincent test	
						// j : numéro du node = data 
						// x / y / w / h pour Vincent 				
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
							// Fonction Victor : EDGES
							// poids = 1 mettre 
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
						char *textlire;
						int i,l;
						fgets(lign,size,fichier);
						sscanf(lign,"%s", test);
						i = atoi(test);
						for (l=0; l <i;l++){
							fgets(lign,size,fichier);
							sscanf(lign,"%s", test);
							if (strcmp("**", test) == 0){
								fgets(lign,size,fichier);
								sscanf(lign,"%s", test);
								printf("\n%s\n", test);
								//token = strtok(str, "_");
								//	while( token != NULL ) {
								//		printf( " %s\n", token );
										//token = strtok(NULL, s);
									//}
								// strcat(textfile, " ");
								//strtok();							
							
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