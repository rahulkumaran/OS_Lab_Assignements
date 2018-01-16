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
	char* readSent;
	shmid = shmget(key,SHMSIZE, IPC_CREAT | 0777);

	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	readSent = shmat(shmid,NULL,0);
	if( readSent == (char*)-1)
	{
		perror("shmat");
		exit(2);
	}

	printf("Shared Memory ID in client: %d\n",shmid);

	printf("%s read from server program\n",readSent);
}
