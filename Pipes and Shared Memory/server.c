#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHMSIZE 100
int main()
{
	key_t key=1234;
	int shmid;
	char *sentence,*s ;
	shmid = shmget(key,SHMSIZE, IPC_CREAT | 0777);

	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	printf("Shared Memory ID: %d\n",shmid);

	sentence = shmat(shmid,NULL,0);
	if( sentence == (char*)-1)
	{
		perror("shmat");
		exit(2);
	}

	s = sentence;
	*s = 'h';
	s++;
	*s = 'i';
	//scanf("%s",&sentence);

	printf("Got \"%s\" from server\n",sentence);

	

	//shmctl(shmid, IPC_RMID, 0);
}
