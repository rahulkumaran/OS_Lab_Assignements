
#ifndef SERVER_H_
#define SERVER_H_
#include "structures.h"

typedef struct node
{
    data_packet* data;
    struct node* next;
} node;

typedef struct list
{
    node* head;
} list;
/* 
	server takes packet from pipe and prints data to user.
	struct data_packet : defined in structures.h

	0 : add student
	1 : modify student
	2 : delete student
	3 : add course
	4 : update course
	5 : delete course
	6 : print DB
*/
int server_init();
list* l;
void create_list();
void print_list();
node* get_student(int);
void create_student(data_packet*);

node* get_student(int rollno)
{
    node* n = l->head;
    while(n!=NULL)
    {
        if(n->data->rollno == rollno)
        return n;
        n = n->next;
    }
    return NULL;
}

void print_student(node* n)
{
	printf("----------\n");
	printf("Name : %s\n",n->data->name);
	printf("Student ID : %d\n",n->data->rollno);
	printf("CGPA : %f\n",n->data->cgpa);
	printf("Number Of Courses : %d\n",n->data->no_of_courses);
	printf("Courses : %s\n",n->data->courses);
}

void create_student(data_packet* data)
{
	node* p = malloc(sizeof(node));
	node* n = l->head;
	p->data=data;

	if(l->head->data->rollno==0)
	{
		l->head=p;
	}
	else
	{
		if(data->rollno < n->data->rollno)
		{
			p->next=l->head;
			l->head=p;
		}
		else
		{
			while(n->next!=NULL && (n->next->data->rollno < p->data->rollno))
				n=n->next;
			p->next=n->next;
			n->next=p;					
		}
	}
}

void modify_student(data_packet* data)
{
	node* old = get_student(data->rollno);
    	old->data->cgpa = data->cgpa;
}

void delete_student(data_packet* data)
{
	node* n = l->head;
	if(n->data->rollno==data->rollno)
		l->head = l->head->next;
	else
		while(n->next != NULL)
		{
		    if(n->next->data->rollno == data->rollno)
			{n->next=n->next->next; return;}
		    n=n->next;
		}
	return ;
}



void print_list()
{
	if(l==NULL)
		{printf("Print : List not found \n");exit(0);}
	node* pointer = l->head;
	printf("Student Database : \n");
	while(pointer)
	{
		print_student(pointer);
		pointer = pointer->next;
	}
	printf("\n");
}

void create_list()
{
	l = malloc(sizeof(list));
	node* n=malloc(sizeof(node));
	l->head=n;
	
	data_packet* req_bloc=malloc(sizeof(data_packet));
	data_init(req_bloc);
	n->data=req_bloc;
}
int server_init(int read_fd,int write_fd)
{

	int idle,client_request;
	create_list();
	while(1)
	{
		idle=1;
		client_request = 0;
		while(idle)
		{
			read(read_fd,&client_request,sizeof(int));		
			if(client_request==1)
			{
				write(write_fd,&client_request,sizeof(int));			
				idle=0;			
			}
			if(client_request==-1)
				exit(0);
		}

		data_packet* request_block = malloc(sizeof(data_packet));//Create Packet		
		read(read_fd,request_block,sizeof(data_packet));//RECIEVE PACKET

		//READ DATA
		//printf("Server : %d - %s\n",request_block->prompt,request_block->courses);
		//Identify command and exec.
	
		switch(request_block->prompt)
		{
			case 0 : //Add Student				
				create_student(request_block);
				 break;
			case 1 : //Modify Student
				modify_student(request_block);				
				 break;
			case 2 : //Delete Student
				 delete_student(request_block);						 
				break;
			case 3 : //Add Course
				// add_course(req_block);
				 break;
			case 4 : //Edit Course
				// edit_course(req_block);
				 break;
			case 5 : //Delete Course
				// delete_course(req_block);
				 break;
			case 6 : print_list();
				break;
			default : printf("Invalid command\n");
		}		
		printf("Server : Command Executed\n\n");	
	}
	return 0;
}
#endif


