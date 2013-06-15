#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json/json.h>

#include "osdetect.h"
#include "search.h"
#include "boolean.h"
#include "error.h"
#include "charappend.h"
#include "input.h"

bool textMode = true;
const bool ask = true;
char execPath [260];

void launchApplication(char *appName){
	// launches an application via the command line
	// does so based on current OS
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
	// display some init information
	// mainly for debugging
	printf("-----INIT-------\n");
	printf("Platform Value:  %i\n", OS);
	printf("-----ENDINIT----\n");

	// initialize execPath
	// put in default values
	strcpy(execPath, ".");
	strcatc(execPath, PATHSEP);

	// parses arguments; 3 necessary for parsing (2 required for arg and argv[0] is always present)
	// only argument currently is executables location
	// activated by "-el path" or "--exec-location path"
	if(argc >= 3){
		if(argc % 2 != 1)
			err("Invalid number of arguments", false);
		else if(strcmp(argv[1], "-el") || strcmp(argv[1], "--exec-location")){
			strcpy(execPath, argv[2]);
			if(execPath[strlen(execPath) - 1] != PATHSEP)
				strcatc(execPath, PATHSEP);
		}
	}

	// make list of executables
	char **list = (char**)malloc(getNumberOfExecutables(execPath) * sizeof(char*));
	for(int i = 0; i < getNumberOfExecutables(execPath); i++)
		list[i] = (char*)malloc(60);
	getExecutables(execPath, list);

	// ask if text mode is desired
	if(ask){
		printf("Would you like to use text mode? y = yes, n = no\n");
		char answer;
		do
			answer = getchar();
		while (isspace(answer));
		textMode = answer == 'y' ? true : false;
	}

	// do stuff according to being in text mode or not
	if(textMode){
		printf("Type the number of the lesson you want to run.\n");
		for(int i = 0; i < getNumberOfExecutables(execPath); i++){
			printf("%i %s\n", i, list[i]);
		}

		// make answer string
		// length of 5 because having more than 9999 lessons is insane
		char answer [5];

		// clear input
		while(getchar() != '\n');

		// get input
		getLineLoop("", answer, sizeof(answer));

		// convert input to int
		int lessonNumber;
		sscanf(answer, "%i", &lessonNumber);

		// parse input
		if(lessonNumber >= 0 && lessonNumber < getNumberOfExecutables(execPath))
			launchApplication(list[lessonNumber]);
		else if(lessonNumber >= getNumberOfExecutables(execPath) || lessonNumber < 0)
			printf("Error:  Input number corresponds to no executable!\n");
		else
			printf("Error!\n");
	}
	else
		printf("Will be implemented soon!\n");

	// free memory taken from executables list
	for(int i = 0; i < getNumberOfExecutables(execPath); i++)
		free(list[i]);
	free(list);
	return 0;
}
