#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include "boolean.h"

#ifndef OK
#define OK 0
#endif
#ifndef NO_INPUT
#define NO_INPUT 1
#endif
#ifndef TOO_LONG
#define TOO_LONG 2
#endif

//thanks to http://stackoverflow.com/questions/4023895/how-to-read-string-entered-by-user-in-c/4023921#4023921 for the great code!
//this will never return NO_INPUT sadly
int getLine(char *prompt, char *buffer, size_t size){
    if(prompt != NULL){
        if(strlen(prompt) != 0)
            printf("%s\n", prompt);
        fflush(stdout);
    }
    if(fgets(buffer, size, stdin) == NULL)
        return NO_INPUT;
    if(buffer[strlen(buffer) - 1] != '\n'){
        int character, extra = 0;
        while(((character = getchar()) != '\n') && (character != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    buffer[strlen(buffer) - 1] = '\0';
    return OK;
}

void getLineLoop(char *prompt, char *buffer, size_t size){
	while(true){
		if(getLine(prompt, buffer, size) == OK)
			break;
		else
			printf("Input too long, please re-enter.\n");
	}
}

#endif
