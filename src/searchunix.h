#ifndef SLINUX_H
#define SLINUX_H

#include <glob.h>

#define PATTERN "./Lesson*"

int getNumberOfExecutables(){
	glob_t result;
	glob(PATTERN, GLOB_ERR, NULL, &result);
	int number = 0;
	for(int i = 0; i < result.gl_pathc; i++)
		if(result.gl_pathv[i] != NULL)
			number++;
	globfree(&result);
	return number;
}

void getExecutables(char **list){
	glob_t result;
	glob(PATTERN, GLOB_ERR, NULL, &result);
	for(int i = 0; i < getNumberOfExecutables(); i++)
		strcpy(list[i], result.gl_pathv[i]);
	globfree(&result);
}

#endif
