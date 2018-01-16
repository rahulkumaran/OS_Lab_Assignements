#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <sys/wait.h>
int main()
{
	int pfd1[2],pfd2[2];
	pid_t pid;
	char buff_read_child[50]="Reading from child to parent";
	char buff_write_parent[50]="";
	char buff_read_parent[50]="Reading from parent and writing in child";
	char buff_write_child[50]="";
	if(pipe(pfd1)==-1)
	perror("Error");

	if(pipe(pfd2)==-1)
	perror("Error2");

	pid = fork();

	if(pid==0)
	{
		printf("In child\n");
		close(pfd1[0]);
		write(pfd1[1],buff_read_child,50);
		printf("Child read: %s\n",buff_read_child);
		close(pfd1[1]);

		close(pfd2[1]);
		read(pfd2[0],buff_write_child,50);
		printf("Child wrote : %s\n",buff_write_child);
		close(pfd2[0]);
	}
	else if(pid > 0)
	{
		printf("In parent\n");
		close(pfd1[1]);
		read(pfd1[0],buff_write_parent,50);
		printf("Parent wrote : %s\n",buff_write_parent);
		close(pfd1[0]);

		close(pfd2[0]);
		write(pfd2[1],buff_read_parent,50);
		printf("Parent read: %s\n",buff_read_parent);
		close(pfd2[1]);	
	}
}
