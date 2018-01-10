
#include "main.h"

int main(void){
  int status=1;
  do {
    pid_t pid;
    int i,j;
    char user_input[STRLEN],input_string[STRLEN], pwd[1024];
    char* command_buffer[BUFF_SIZE]={0};  char* path_buffer[BUFF_SIZE]={0};
    char* token;  char* path=getenv("PATH");
    char* token1; char * token2;char* temp;char* buff;
    char* cd_buffer[STRLEN];    char user_input2[STRLEN];
    long size;


    getcwd(pwd, sizeof(pwd));
    printf("%sBombShell:%s%s%s$ ", GREEN,CYAN,pwd,WHITE);
    fgets(user_input, STRLEN, stdin);
    strcpy(user_input2,user_input);

    for (int k = 0; k < STRLEN; k++)
      if (user_input[k]=='\n'){
        user_input[k]='\0'; break;
      }
    strcpy(input_string,user_input);

    //parse input string
    token=strtok(input_string," ");
    i=0;
     while (token){
      command_buffer[i]=token;
      token=strtok(NULL," ");
      i++;
    }
    command_buffer[i]=NULL;

    /////////////////////SHELL BUILTIN COMMANDS//////////////////////

    token1=strtok(user_input2,"\n");
    token2=strtok(user_input2," ");
    i=0;
    while (token2) {
      cd_buffer[i]=token2;
      token2=strtok(NULL," ");
      i++;
    }
    cd_buffer[i]=NULL;
    size=pathconf(".",_PC_PATH_MAX);
    if ((temp=(char*) malloc( (size_t) size)))
      buff=getcwd(temp,(size_t) size);

    if (strcmp(cd_buffer[0],"cd")==0) {            //CD
      ChangeDir(token1,buff,cd_buffer);continue;
    }
    if (strcmp(command_buffer[0],"exit")==0) {    //EXIT
      break;
    }
    /////////////////////SHELL BUILTIN COMMANDS END///////////////////////
    //creating child Process
    pid=fork();
    if (pid==0)
    {
      //parse path string
      token=strtok(path,":");
      i=0;
       while (token){
        path_buffer[i]=token;
        token=strtok(NULL,":");
        i++;
      }
      path_buffer[i++]=pwd;
      path_buffer[i]=NULL;
      //Exec
      for(j=0;j<i;j++){
        char command[BUFF_SIZE];
        strcpy(command,path_buffer[j]); strcat(command,"/");  strcat(command,command_buffer[0]);
        execv(command,command_buffer);
        }
      printf("%s: command not found\n",command_buffer[0]);
      break;
    }
    else if (pid>0)
      wait(NULL);
    else
      printf("Process failed \n");
  } while(status);
  return 0;
}
