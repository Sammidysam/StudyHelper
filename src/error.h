#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#include "boolean.h"

// handles errors
void err(const char *message, bool terminate){
	printf("ERROR: %s!\n", message);
	if(terminate)
		exit(-1);
}

#endif
