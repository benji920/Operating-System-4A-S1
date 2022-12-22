#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

pid_t process1=fork();

    if (process1 == 0 ){// we enter in the first child process because fork return 0
        printf("I am the first 1st-level child process\n");
        
    }
    else {
        pid_t process2=fork();
    if(process2==0)
    {
       printf("I am the second 1st-level child process\n"); 
       pid_t process3=fork();
       if(process3 == 0)
        printf("I am the 2nd-level child process\n");
    }

    }

}