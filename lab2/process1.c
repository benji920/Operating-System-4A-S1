#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h> 
#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv) {
int id; int i; char *ptr; 
//system("ipcs -m");
id = shmget(KEY, sizeof(char), IPC_CREAT | PERMS);
ptr = (char *) shmat(id, NULL, 0);
printf("What value do you want to copy to process 2?\n");
scanf("%s",ptr);
}