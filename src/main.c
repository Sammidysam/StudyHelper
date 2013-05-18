#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osdetect.h"
#include "search.h"

int textMode = 1;
const int ask = 1;

void clearInput(){
	while (getchar() != '\n');
}

void launchApplication(char *appName){
	char command [60];
	switch (OS){
		case WINDOWS:
			strcpy(command, appName);
			system(command);
			break;
		case LINUX:
			strcpy(command, "./");
			strcat(command, appName);
			system(command);
			break;
		case MAC:
			// untested code
			strcpy(command, "open -n ./");
			strcat(command, appName);
			system(command);
			break;
		default:
			printf("Illegal OS value!\n");
			break;
	}
}

int main(int argc, char *argv[]){
	printf("-----INIT-------\n");
	printf("Platform Value:  %i\n", OS);
	printf("-----ENDINIT----\n");
	char **list = (char**)malloc(getNumberOfExecutables() * sizeof(char*));
	for(int i = 0; i < getNumberOfExecutables(); i++)
		list[i] = (char*)malloc(60);
	getExecutables(list);
	if(ask){
		printf("Would you like to use text mode? y = yes, n = no\n");
		char answer;
		do
			answer = getchar();
		while (isspace(answer));
		textMode = answer == 'y' ? 1 : 0;
	}
	if(textMode){
		printf("Type the number of the lesson you want to run.\n");
		for(int i = 0; i < getNumberOfExecutables(); i++){
			printf("%i %s\n", i, list[i]);
		}
		char answer;
		clearInput();
		do
			answer = getchar();
		while (isspace(answer));
		if(answer >= 48 && answer < 48 + getNumberOfExecutables())
			launchApplication(list[answer - '0']);
		else if(answer >= 48 + getNumberOfExecutables() && answer <= 57)
			printf("Error:  Input number corresponds to no executable!\n");
		else
			printf("Error!\n");
	}
	else
		printf("Will be implemented soon!\n");
	for(int i = 0; i < getNumberOfExecutables(); i++)
		free(list[i]);
	free(list);
	return 0;
}


