#ifdef _WIN64
#define OS 0
#elif _WIN32
#define OS 0
#elif __APPLE__
#define OS 2
#elif __linux
#define OS 1
#elif __unix
#define OS 1
#elif __posix
#define OS 1
#else
#define OS -1
#endif

#define WINDOWS 0
#define LINUX 1
#define MAC 2

#include <stdio.h>
#include <string.h>

void launchApplication(char *appName){
	char command [60];
	switch (OS){
		case WINDOWS:
			strcpy(command, appName);
			system(command);
			break;
		case LINUX:
			strcpy(command, "./");
			strcat(command, appName);
			system(command);
			break;
		case MAC:
			// untested code
			strcpy(command, "open -n ./");
			strcat(command, appName);
			system(command);
			break;
		default:
			printf("Illegal OS value!\n");
			break;
	}
}

int main(int argc, char *argv[]){
	printf("-----INIT-------\n");
	printf("Platform Value:  %i\n", OS);
	printf("-----ENDINIT----\n");
	launchApplication("LessonSpanish");
}


