#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../input.h"
#include "files.h"
#include "errorlog.h"
#include "../boolean.h"
#include "../osdetect.h"
#include "../charappend.h"

char questionFile [260], answerFile [260];
bool checkCorrect = false;
//note: checkCorrect does not work.  It marks everything as incorrect.  Only turn to true when compiling if you are fixing it.

int main(int argc, char *argv[]){
	printf("All lessons should be in the lessons directory.\n");
	printf("When prompted, just type the name of the lesson.  Do not type the file extension or the directory it is in.\n");
	printf("For example, if you had the lesson with question file 4BQ.txt and answer file 4BA.txt in the lessons folder, you would simply type \"4BQ.txt\" for the question file and \"4BA.txt\" for the answer file.\n");
	strcpy(questionFile, "lessons");
	strcpy(answerFile, "lessons");
	strcatc(questionFile, PATHSEP);
	strcatc(answerFile, PATHSEP);
	char name [260];
	getLineLoop("Type the name of the questions file.\n", name, sizeof(name));
	strcat(questionFile, name);
	strcat(questionFile, ".txt");
	getLineLoop("Type the name of the answers file.\n", name, sizeof(name));
	strcat(answerFile, name);
	strcat(answerFile, ".txt");
	srand(time(NULL));
	const int lines = getLines(questionFile, answerFile);
	if(lines < 0)
		return lines;
	char question [256], answer [256], input [256];
	bool done = false;
	printf("Type 'stop' to stop.\n");
	while(!done){
		int questionLine = rand() % lines;
		getFileLine(question, questionLine, questionFile);
		printf("%s", question);
		getLineLoop("", input, sizeof(input));
		for(int i = 0; input[i]; i++)
			input[i] = tolower(input[i]);
		if(strcmp(input, "stop") == 0)
			done = true;
		if(!done){
			getFileLine(answer, questionLine, answerFile);
			if(!checkCorrect)
				printf("%s", answer);
			else {
				for(int j = 0; answer[j]; j++)
					answer[j] = tolower(answer[j]);
				if(strcmp(input, answer) == 0)
					printf("Correct!\n");
				else
					printf("Incorrect!\n");
			}
		}
	}
	return 0;
}
