#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <string.h>
#include "errorlog.h"
#include "boolean.h"

bool checkExistance(FILE *file, char *name, bool print){
	if(print && !file){
		char message [40];
		printf("No file by the name ");
		sprintf(message, "%s", "No file by the name ");
		printf("%s\n", name);
		sprintf(message + strlen(message), "%s", name);
		logError(message);
	}
	return file ? true : false;
}

int getLines(char *questionFile, char *answerFile){
	FILE *question = fopen(questionFile, "r");
	FILE *answer = fopen(answerFile, "r");
	if(!checkExistance(question, questionFile, true) || !checkExistance(answer, answerFile, true)){
		fclose(question);
		fclose(answer);
		return -1;
	}
	char line [256];
	int questionLines = 0, answerLines = 0;
	while(fgets(line, 256, question) != NULL){
		questionLines++;
	}
	while(fgets(line, 256, answer) != NULL){
		answerLines++;
	}
	if(questionLines != answerLines){
		printf("The number of lines in the two files are different!  This will cause problems, so you should check that out.\n");
		logError("Number of lines in question and answer files are different.\n");
		return -2;
	}
	fclose(question);
	fclose(answer);
	return questionLines;
}

void getFileLine(char *string, int line, char *fileName){
	FILE *answer = fopen(fileName, "r");
	if(checkExistance(answer, fileName, true)){
		int localLine = 0;
		for(localLine = 0; localLine < line + 1; localLine++){
			if(fgets(string, 256, answer) == NULL)
				break;
		}
		fclose(answer);
	}
}

#endif
