#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
int i = 5;
if (fork() == 0) {
execl("/bin/google-chrome","ece.fr", NULL); 
printf("%d\n", i); // is this line executed ? why ?
} else{
int pid_t = getpid();
        printf("my pid is %d\n", pid_t);}
}