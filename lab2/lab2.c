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
int id; int i; int *ptr;
//system("ipcs -m");
id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);

ptr = (int *) shmat(id, NULL, 0);
*ptr = 0; i = 54;
if (fork() == 0)
{ //P1
int a=1;
int b=2;
int result=a+b ;
*ptr=result;
} else {
//P2
wait(NULL);
int c=3;
int d=4;
int result=c+d;
*ptr=(*ptr)*result;

if (fork()==0){
//P3
    int e=5;
    int f=6;
    int result=e+f;
    *ptr=(*ptr)*result;
}
else{
wait(NULL);
printf("Value of *ptr = %d\n", *ptr);
shmctl(id, IPC_RMID, NULL);}
}
}
