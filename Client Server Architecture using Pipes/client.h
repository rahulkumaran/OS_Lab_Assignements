
#ifndef CLIENT_H_
#define CLIENT_H_
#include "structures.h"
int client_init();
int server_is_ready(int,int);
int client_request;
int server_ready=0;
/*
    0 : add student
    1 : modify student
    2 : delete student
    3 : add course
    4 : update course
    5 : delete course
    6 : print DB
*/

int client_init(int read_fd,int write_fd)
{    
    FILE* stream;
    char read_string[255];
    stream= fopen("input.txt","r");

    if(stream==NULL)
    {
    	printf("Client: Input file not found\n");
    	exit(0);
    }
    else
    {
        fgets(read_string, 255, (FILE*)stream);    
        while(feof(stream)!=1)
        {    
            if(server_is_ready(read_fd,write_fd))
            {        
                data_packet* request_block = malloc(sizeof(data_packet)); //CREATE PACKET        
                data_init(request_block);//Init Packet

		//Assign Packet
                char* command =strtok(read_string,":");
		printf("Client: %s request made\n",command);
                if(strncasecmp(command,"Add Student",STRLEN)==0)
                {
                    request_block->prompt=0;        
                    request_block->rollno=atoi(strtok(NULL,":"));
                    strcpy(request_block->name,strtok(NULL,":"));
                    request_block->cgpa=atof(strtok(NULL,":"));
                    request_block->no_of_courses =atoi( strtok(NULL,":"	));
		    for(int i=0;i<request_block->no_of_courses*2;i++)
			{
				char* token=strtok(NULL,":");
				strcat(request_block->courses,token);
				strcat(request_block->courses,":");
			}
                }             
                else if(strncasecmp(command, "Modify Student",STRLEN)==0)
                {
                    request_block->prompt = 1;
                    request_block->rollno = atoi(strtok(NULL,":"));
                    request_block->cgpa = atof(strtok(NULL,":"));
                }
		else if(strncasecmp(command,"Delete Student",STRLEN)==0)
                {
                    request_block->prompt=2;
                    request_block->rollno=atoi(strtok(NULL,":"));
                }
                else if(strncasecmp(command ,"Add Course",STRLEN)==0)
                {
                    request_block->prompt = 3;
                    request_block->rollno = atoi(strtok(NULL,":"));
                    for(int i=0;i<request_block->no_of_courses*2;i++)
			{
				char* token=strtok(NULL,":");
				strcat(request_block->courses,token);
				strcat(request_block->courses,":");
			} 
                }
                else if(strncasecmp(command,"Modify Course",STRLEN)==0)
                {
                    request_block->prompt = 4;
                    request_block->rollno = atoi(strtok(NULL,":"));
                    for(int i=0;i<request_block->no_of_courses*2;i++)
			{
				char* token=strtok(NULL,":");
				strcat(request_block->courses,token);
				strcat(request_block->courses,":");
			} 
                }
                else if(strncasecmp(command,"Delete Course",STRLEN)==0)
                {
                    request_block->prompt = 5;
                    request_block->rollno = atoi(strtok(NULL,":"));
                    for(int i=0;i<request_block->no_of_courses*2;i++)
			{
				char* token=strtok(NULL,":");
				strcat(request_block->courses,token);
				strcat(request_block->courses,":");
			} 
                }
		else if(strncasecmp(command,"Print DataBase",STRLEN)==0)
		{
			request_block->prompt = 6;
		}
                else
                {
                    printf("I am sorry but I do not know how to perform the task you asked for!\n");
                    printf("Please check your commands again\n");
                }
                write(write_fd,request_block,sizeof(data_packet));//SEND REQUEST BLOCK
                fgets(read_string, 255, (FILE*)stream);    
            }    
        }
    }
    fclose(stream);

    //End Connection
    client_request=-1;
    write(write_fd,&client_request,sizeof(int));
    return 0;
}

int server_is_ready(int read_fd,int write_fd)
{
	int client_request =1;            
	write(write_fd,&client_request,sizeof(int));
	while(1)            
	{
		read(read_fd,&server_ready,sizeof(int));
		if(server_ready==1)
		    return 1;
	}
}

#endif 
