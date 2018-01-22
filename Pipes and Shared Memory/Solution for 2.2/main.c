#include "shmcsa.h"

int main()
{
	int serverShmid, clientShmid;
	printf("-----------------------------------------------------------\n\n");
	serverShmid = server();
	printf("-----------------------------------------------------------\n\n");
	clientShmid = client();
	printf("-----------------------------------------------------------\n\n");

	/*The client and server shmid's will be the
	same you can check it by seeing O/P of the line below.*/
	printf("Server SHMID : %d\nClient SHMID : %d\n",serverShmid, clientShmid);


	/*Uncomment the line below to clear the shared memory space*/
	//shmctl(serverShmid, IPC_RMID, 0);
}
