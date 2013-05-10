#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "input.h"
#include "files.h"
#include "errorlog.h"
#include "boolean.h"

char questionFile [260], answerFile [260];
bool checkCorrect = false;
//note: checkCorrect does not work.  It marks everything as incorrect.  Only turn to true when compiling if you are fixing it.

int main(int argc, char *argv[]){
	getLineLoop("Type the name of the questions file.\n", questionFile, sizeof(questionFile));
	strcat(questionFile, ".txt");
	getLineLoop("Type the name of the answers file.\n", answerFile, sizeof(answerFile));
	strcat(answerFile, ".txt");
	srand(time(NULL));
	const int lines = getLines(questionFile, answerFile);
	if(lines < 0)
		return lines;
	char question [256], answer [256], input [256];
	int questionLine;
	bool done = false;
	printf("Type 'stop' to stop.\n");
	while(!done){
		questionLine = rand() % lines;
		getFileLine(question, questionLine, questionFile);
		printf("%s", question);
		getLineLoop("", input, sizeof(input));
		int i = 0;
		for(i = 0; input[i]; i++)
			input[i] = tolower(input[i]);
		if(strcmp(input, "stop") == 0)
			done = true;
		if(!done){
			getFileLine(answer, questionLine, answerFile);
			if(!checkCorrect)
				printf("%s", answer);
			else {
				int j = 0;
				for(j = 0; answer[j]; j++)
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
