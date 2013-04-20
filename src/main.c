#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"
#include "input.h"

char questionFile [260], answerFile [260];
bool checkCorrect = false;

bool checkExistance(FILE *file, char *name, bool print){
	if(print && !file){
		printf("No file by the name ");
		printf("%s\n", name);
	}
	return file ? true : false;
}

int getLines(){
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
		return -2;
	}
	fclose(question);
	fclose(answer);
	return questionLines;
}

void getAnswer(char *string, int line){
	FILE *answer = fopen(answerFile, "r");
	if(checkExistance(answer, answerFile, true)){
		int localLine = 0;
		for(localLine = 0; localLine < line + 1; localLine++){
			if(fgets(string, 256, answer) == NULL)
				break;
		}
		fclose(answer);
	}
}

void getQuestion(char *string, int line){
	FILE *question = fopen(questionFile, "r");
	if(checkExistance(question, questionFile, true)){
		int localLine = 0;
		for(localLine = 0; localLine < line + 1; localLine++){
			if(fgets(string, 256, question) == NULL)
				break;
		}
		fclose(question);
	}
}

int main(int argc, char *argv[]){
	getLineLoop("Type the name of the questions file.\n", questionFile, sizeof(questionFile));
	strcat(questionFile, ".txt");
	getLineLoop("Type the name of the answers file.\n", answerFile, sizeof(answerFile));
	strcat(answerFile, ".txt");
	srand(time(NULL));
	const int lines = getLines();
	if(lines < 0)
		return lines;
	char question [256], answer [256], input [256];
	int questionLine;
	bool done = false;
	printf("Type 'stop' to stop.\n");
	while(!done){
		questionLine = rand() % lines;
		getQuestion(question, questionLine);
		printf("%s", question);
		getLineLoop("", input, sizeof(input));
		int i = 0;
		for(i = 0; input[i]; i++)
			input[i] = tolower(input[i]);
		if(strcmp(input, "stop") == 0)
			done = true;
		if(!done){
			getAnswer(answer, questionLine);
			printf("%s", answer);
		}
	}
	return 0;
}
