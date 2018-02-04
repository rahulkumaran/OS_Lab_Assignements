#include "server.h"
#include "client.h"
int main(void)
{
	int fd1[2],fd2[2];

	pipe(fd1);	// server to client 
	pipe(fd2);	// client to server 
	
	pid_t pid = fork();
	
	if(pid==0)
		client_init(fd1[0],fd2[1]);	// Initiates Client Process
	else if(pid>0)
		server_init(fd2[0],fd1[1]);	// Initiates Server Process
	else
		printf("Fork Error\n");		

	return 0;
}






