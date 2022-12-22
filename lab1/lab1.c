#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {


    if (fork() == 0){// we enter in the child process because fork return 0
        printf("I am the child\n");
        int pid_t = getpid();
        printf("my pid is %d\n", pid_t);
    }
  
    //we get out of the child process and operate in the parent process
    else
       { printf("I am the parent\n");
        int pid_t = getpid();
        printf("my pid is %d\n", pid_t);
       }

}