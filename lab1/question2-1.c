#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
int pid_t = getpid();
        printf("my pid is %d\n", pid_t);
    
    execl("/bin/google-chrome","ece.fr", NULL);

}