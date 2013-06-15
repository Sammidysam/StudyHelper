#ifndef SWINDOWS_H
#define SWINDOWS_H

#include <windows.h>
#include <string.h>

#define PATTERN "Lesson*"

int getNumberOfExecutables(char *dir){
	char pattern [260];
	strcpy(pattern, dir);
	strcat(pattern, PATTERN);
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(pattern, &data);
	if(hFind == INVALID_HANDLE_VALUE)
		return 0;
	int number = 1;
	while (FindNextFile(hFind, &data) != 0)
		number++;
	FindClose(hFind);
	return number;
}

void getExecutables(char *dir, char **list){
	char pattern [260];
	strcpy(pattern, dir);
	strcat(pattern, PATTERN);
	if(getNumberOfExecutables() < 1)
		return;
	WIN32_FIND_DATA lesson;
	HANDLE hFind = FindFirstFile(pattern, &lesson);
	strcpy(list[0], lesson.cFileName);
	for(int i = 1; i < getNumberOfExecutables(); i++){
		FindNextFile(hFind, &lesson);
		strcpy(list[i], lesson.cFileName);
	}
	FindClose(hFind);
}

#endif
