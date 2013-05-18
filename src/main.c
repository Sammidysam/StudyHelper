#ifdef _WIN64
#define OS 0
#elif _WIN32
#define OS 0
#elif __APPLE__
#define OS 2
#elif __linux
#define OS 1
#elif __unix
#define OS 1
#elif __posix
#define OS 1
#else
#define OS -1
#endif

#define WINDOWS 0
#define LINUX 1
#define MAC 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

const char *pattern = OS == WINDOWS ? ".\\Lesson*" : "./Lesson*";
int textMode = 1;
const int ask = 1;

void clearInput(){
	while (getchar() != '\n');
}

int getNumberOfExecutables(){
	glob_t result;
	glob(pattern, GLOB_ERR, NULL, &result);
	int number = 0;
	for(int i = 0; i < result.gl_pathc; i++)
		if(result.gl_pathv[i] != NULL)
			number++;
	globfree(&result);
	return number;
}

void getExecutables(char **list){
	glob_t result;
	glob(pattern, GLOB_ERR, NULL, &result);
	for(int i = 0; i < getNumberOfExecutables(); i++)
		strcpy(list[i], result.gl_pathv[i]);
	globfree(&result);
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


