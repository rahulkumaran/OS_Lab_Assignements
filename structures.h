#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define STRLEN 15
#define BUFF_SIZE 255

struct data_packet
{
	int prompt;
	int no_of_courses;
	char courses[BUFF_SIZE];
	char name[STRLEN];
	int rollno;
	float cgpa;
	
};
typedef struct data_packet data_packet;
void data_init(data_packet* data)
{
    data = malloc(sizeof(data_packet));
    data->prompt = 0;
    strcpy(data->courses,"");
    strcpy(data->name,"");
    data->rollno = 0;
    data->cgpa = 0.0;
}
#endif
