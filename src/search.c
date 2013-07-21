#include "osdetect.h"
#include "search.h"

#if OS == WINDOWS
#include <windows.h>
#else
#include <glob.h>
#endif
#include <string.h>

#define PATTERN "Lesson*"

int getNumberOfExecutables(char *dir)
{
    char pattern [260];
    strcpy(pattern, dir);
    strcat(pattern, PATTERN);
    #if OS == WINDOWS
    WIN32_FIND_DATA data;
    HANDLE hFind = FindFirstFile(pattern, &data);
    if(hFind == INVALID_HANDLE_VALUE)
        return 0;
    int number = 1;
    while (FindNextFile(hFind, &data) != 0)
        number++;
    FindClose(hFind);
	#else
    glob_t result;
    glob(pattern, GLOB_ERR, NULL, &result);
    int number = 0;
    for(int i = 0; i < result.gl_pathc; i++)
        if(result.gl_pathv[i] != NULL)
            number++;
    globfree(&result);
	#endif
    return number;
}

void getExecutables(char *dir, char **list)
{
	#if OS == WINDOWS
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
	#else
    char pattern [260];
    strcpy(pattern, dir);
    strcat(pattern, PATTERN);
    glob_t result;
    glob(pattern, GLOB_ERR, NULL, &result);
    for(int i = 0; i < getNumberOfExecutables(dir); i++)
        strcpy(list[i], result.gl_pathv[i]);
    globfree(&result);
	#endif
}
