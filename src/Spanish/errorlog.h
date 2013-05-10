#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void logError(char *string){
	srand(time(NULL));
	char errorName [13];
	strcat(errorName, "error");
	int i = 0;
	for(i = 0; i < 10; i++)
		sprintf(errorName + strlen(errorName), "%i", rand() % 10);
	strcat(errorName, ".txt");
	printf("Error logged in ");
	printf("%s\n", errorName);
	time_t timet = time(NULL);
	char *time_string = ctime(&timet);
	FILE *file = fopen(errorName, "w+");
	fprintf(file, "On %s", time_string);
	fprintf(file, "The following error was produced:\n");
	fprintf(file, "\t%s", string);
	fclose(file);
}

#endif
