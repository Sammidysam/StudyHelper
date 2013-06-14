#ifndef SWINDOWS_H
#define SWINDOWS_H

#include <windows.h>

#define PATTERN ".\\Lesson*"

int getNumberOfExecutables(){
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(PATTERN, &data);
	if(hFind == INVALID_HANDLE_VALUE)
		return 0;
	int number = 1;
	while (FindNextFile(hFind, &data) != 0)
		number++;
	FindClose(hFind);
	return number;
}

void getExecutables(char **list){
	if(getNumberOfExecutables() < 1)
		return;
	WIN32_FIND_DATA lesson;
	HANDLE hFind = FindFirstFile(PATTERN, &lesson);
	strcpy(list[0], lesson.cFileName);
	for(int i = 1; i < getNumberOfExecutables(); i++){
		FindNextFile(hFind, &lesson);
		strcpy(list[i], lesson.cFileName);
	}
	FindClose(hFind);
}

#endif
