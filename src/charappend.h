#ifndef CHARAPPEND_H
#define CHARAPPEND_H

void strcatc(char *string, char character){
	int length = strlen(string);
	string[length] = character;
	string[length + 1] = '\0';
}

#endif
