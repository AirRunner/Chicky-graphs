#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mission{
	//array of nodes fonction victor ?
	// array of edges fonction victor ?
	//FileNode;  mettre une array de list ( chaque array correspond a un Node + chaque liste correspond à ses coordonnées
}M_ission;


typedef struct Node{
	char texture;
	int x;
	int y;
	int w;
	int h;
	int data;
}N_ode;

typedef struct Edge{
	int Directed; // (-1): no graph (0): undirected (1): directed  
	int N1_data;	//chemin de N1_data à N2_data 
	int N2_data;
	
}

void readFile(const char* mission){
	FILE * fichier = NULL;
	long nb;
	char target[40];
	int size = 40;
	int len;
	//char compare[40] =	"Graph\n";
	fichier = fopen(mission, "r");
	if (fichier != NULL){
		fgets(target, size, fichier);
		printf("%d",strcmp("Graph",target));
	}
}



void functiontest(const char *name){
	FILE *fichier = NULL;
	fichier = fopen(name, "r");
	int size = 1000;
	char *sentence = (char*)malloc(sizeof(char));
	int ret;
	//char text[1000] = "Graph";
	if (fichier != NULL){
		fgets(sentence, size, fichier);
		//sentence[strlen(sentence)-1] = '\0';
		printf("%s", sentence);
		ret = strcmp(sentence, "Graph");
		if (ret == 0){
			printf("TEST");
		}
		//if (strcmp(sentence,text) == 0){
		//	printf("TEST");
		//	if (strcmp(fgets(sentence, size, fichier),"FALSE" ) == 0 ){
		//		printf("TEST");
		//	}
		

	}
	
}

int main() {
	
	readFile("../data/missions/Mission3.txt");
	
	
	return(0);
}




/*
do{
		fgets(sentence, size , fichier);
		printf("%s", sentence);
	}while (fgets(sentence, size, fichier) != NULL);
	
	
char* Mission_3 =ReadOnFileMission("../data/missions/Mission3.txt");
printf("The file  contains this text\n\n%s", Mission_3);

char* Mission_1 =ReadOnFileMission("Mission1.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_1);
	
char* Mission_2 =ReadOnFileMission("Mission2.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_2);
	
char* Mission_3 =ReadOnFileMission("Mission3.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_3);
	
char* Mission_4 =ReadOnFileMission("Mission4.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_4);
	
char* Mission_5 =ReadOnFileMission("Mission5.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_5);
					
char* Mission_6 =ReadOnFileMission("Mission6.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_6);
	
char* Mission_7 =ReadOnFileMission("Mission7.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_7);
		
char* Mission_8 =ReadOnFileMission("Mission8.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_8);
		
char* Mission_9 =ReadOnFileMission("Mission9.txt");
printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_9);
*/



/*

void Missions(){
		
	char* Mission_10 =ReadOnFileMission("IDEE.txt");
	printf("\n\n\n\nThe file  contains this text\n\n%s", Mission_10);
}


 
idée de séparation 
==> strcpy 

==> strtok : https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/

ex 
split=strtok(buffer,"");

while(split != NULL)
{
	word=split;
	split=strtok(NULL,"-------Nodes-----");
}


idée mettre entre chaque point important --------------- pour faire la distinction


https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split


size =  printf("%lu", sizeof(buffer)); 

*/


/*char *ReadOnFileMission(const char *name){
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
}*/