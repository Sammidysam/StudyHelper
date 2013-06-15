#ifndef SLINUX_H
#define SLINUX_H

#include <glob.h>
#include <string.h>

#define PATTERN "Lesson*"

int getNumberOfExecutables(char *dir){
	char pattern [260];
	strcpy(pattern, dir);
	strcat(pattern, PATTERN);
	glob_t result;
	glob(pattern, GLOB_ERR, NULL, &result);
	int number = 0;
	for(int i = 0; i < result.gl_pathc; i++)
		if(result.gl_pathv[i] != NULL)
			number++;
	globfree(&result);
	return number;
}

void getExecutables(char *dir, char **list){
	char pattern [260];
	strcpy(pattern, dir);
	strcat(pattern, PATTERN);
	glob_t result;
	glob(pattern, GLOB_ERR, NULL, &result);
	for(int i = 0; i < getNumberOfExecutables(dir); i++)
		strcpy(list[i], result.gl_pathv[i]);
	globfree(&result);
}

#endif
