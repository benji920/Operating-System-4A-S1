#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


 void mySystem(const char * command){
     if (fork() == 0)
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        else
        wait(NULL);
 }

 int main(){
    int choix;
    do{
    printf("1. run a program\n");
    printf("2. kill a process\n");
    printf("3. list files\n");
    printf("4. quit\n");
    scanf("%d",&choix);
    switch(choix){
        case 1:
        {
           printf("Type the program you want to run\n");
           char inputText[30];       	    
    	   scanf("%s",inputText);
   	   mySystem(inputText);
   
        break;
        }
        case 2:
        {
           mySystem("ps -e");
           printf("type the pid of the process you want to kill\n");
           char input[6];
           scanf("%s",input);
           char input2[30]="kill ";
           strcat(input2,input);
           mySystem(input2);
    	   break;
        }
        case 3:{
            mySystem("ls");
            break;
        }
        case 4:
            exit(1);
            break;
    }
    }while(choix != 4);
 }
