#ifdef _WIN64
#define OS 0
#elif _WIN32
#define OS 0
#elif __APPLE__
#define OS -1
#elif __linux
#define OS 1
#elif __unix
#define OS 1
#elif __posix
#define OS 1
#endif

#include <stdio.h>

int main(int argc, char *argv[]){
	printf("Platform Value:  %d\n", OS);
	if(OS == 1)
		system("./LessonSpanish");
	else if(OS == 0)
		system("LessonSpanish.exe");
	else
		printf("Your platform is not supported!\n");
}


