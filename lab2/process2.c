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
//system("ipcs -m");
printf("Press any key to paste the value from process 1\n");
getchar();
printf("The pasted value is : %s\n",ptr);
shmctl(id, IPC_RMID, NULL);

}