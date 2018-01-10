#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 15
#endif

#ifndef STRLEN
#define STRLEN 255
#endif

#ifndef CYAN
#define CYAN "\x1B[0;36m"
#endif

#ifndef WHITE
#define WHITE "\x1B[0;37m"
#endif

#ifndef GREEN
#define GREEN "\x1B[1;32m"
#endif

void ChangeDir(char* command,char *CWD, char *Args[STRLEN]){
	int Modify = 0;
	char tempDir[STRLEN];
	strcpy(tempDir, CWD);
	int count = 0, temp = 0;

	if (Args[1] == NULL || strcmp (Args[1], "") == 0){
		Modify = 1;
		chdir("/home");
		getcwd(CWD, STRLEN);
	}
	else if ( Args[1][0] == '/' ){
		Modify = 1;
		chdir(Args[1]);
		getcwd(CWD,STRLEN);
	}
	else if ( strcmp(Args[1], "..") == 0 ){
		while ( tempDir[count] != '\0' ) {
			if ( tempDir[count] == '/' ){
				temp = count;
			}
			count++;
		}
		tempDir[temp] = '\0';
	}
	else {
		strcat(tempDir, "/");
		strcat(tempDir, Args[1]);
	}
	if ( Modify == 0){
		if ( chdir(tempDir) == -1)
			printf("%s\n", strerror(errno));
		else
			getcwd(CWD, STRLEN);
  }
}
