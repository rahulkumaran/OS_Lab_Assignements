#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SHM_SIZE
#define SHM_SIZE 100
#endif

#ifndef USER_INPUT_SIZE
#define USER_INPUT_SIZE 20
#endif


int server()
{
	key_t key=1234;
	int shmid;
	char *sentence,*sent;

	shmid = shmget(key,SHM_SIZE, IPC_CREAT | 0777);

	printf("CURRENTLY RUNNING SERVER PROGRAM!\n\n");


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

	sent = sentence;
	
	printf("\nEnter some text of your choice with a max length of 20 characters:\n");
	fgets(sent,USER_INPUT_SIZE,stdin);

	sent[strlen(sent)-1] = '\0';	//Manipulating user inputted string by removing the '\n' in the end

	printf("\nGot \"%s\" from user in server program\n",sent);

	printf("\nSERVER PROGRAM ENDS!\n\n");

	return shmid;
}



int client()
{
	key_t key=1234;
	int shmid;
	char* readSent;

	shmid = shmget(key,SHM_SIZE, IPC_CREAT | 0777);

	printf("CURRENTLY RUNNING CLIENT PROGRAM!\n\n");
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

	
	printf("Shared Memory ID in client: %d\n\n",shmid);

	printf("\"%s\" read from server program in client program\n",readSent);

	printf("\nCLIENT PROGRAM ENDS!\n\n");

	return shmid;
}
