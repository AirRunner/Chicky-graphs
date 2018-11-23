#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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


void Missions(){
	char* Mission_1 =ReadOnFileMission("Mission1.txt");
		printf("The file  contains this text\n\n%s", Mission_1);
		
		printf(ANSI_COLOR_BLUE"______________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
		
		char* Mission_2 =ReadOnFileMission("Mission2.txt");
		printf("The file  contains this text\n\n%s", Mission_2);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
		
		char* Mission_3 =ReadOnFileMission("Mission3.txt");
		printf("The file  contains this text\n\n%s", Mission_3);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
			
		char* Mission_4 =ReadOnFileMission("Mission4.txt");
		printf("The file  contains this text\n\n%s", Mission_4);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
			
		char* Mission_5 =ReadOnFileMission("Mission5.txt");
		printf("The file  contains this text\n\n%s", Mission_5);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
				
		char* Mission_6 =ReadOnFileMission("Mission6.txt");
		printf("The file  contains this text\n\n%s", Mission_6);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
		
		char* Mission_7 =ReadOnFileMission("Mission7.txt");
		printf("The file  contains this text\n\n%s", Mission_7);
		
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
			
		char* Mission_8 =ReadOnFileMission("Mission8.txt");
		printf("The file  contains this text\n\n%s", Mission_8);
			
		printf(ANSI_COLOR_BLUE"____________________________________________________________________________________________________________________\n");
		printf(ANSI_COLOR_RESET"");
				
		char* Mission_9 =ReadOnFileMission("Mission9.txt");
		printf("The file  contains this text\n\n%s", Mission_9);
		
}


int main() {
	
	Missions();
	
	
	return(0);
}