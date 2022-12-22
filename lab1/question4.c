#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
int i = 5;
if (fork() ==0) { // I’m the child process
i++;
} 
else { //I’m the parent process
sleep(3); // sleep for 3 seconds
printf("%d\n", i);
}
}