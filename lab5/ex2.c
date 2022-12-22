#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#define KEY 4567
#define PERMS 0660

int main(int argc, char **argv)
{
    int id;
    int *i;
    int sem_id;
    int sem_id2;
    int sem_id3;
    id = shmget(KEY, sizeof(int), IPC_CREAT | PERMS);
    i = (int *)shmat(id, NULL, 0);
    *i = 65;
    register int Reg;
    sem_t *sem;
    sem_t *sem2;
    sem_t *sem3;
    sem_id = shmget(KEY + 1, sizeof(sem_t), IPC_CREAT | PERMS);
    sem = (sem_t *)shmat(sem_id, NULL, 0);
    sem_id2 = shmget(KEY + 2, sizeof(sem_t), IPC_CREAT | PERMS);
    sem2 = (sem_t *)shmat(sem_id2, NULL, 0);
    sem_id3 = shmget(KEY + 3, sizeof(sem_t), IPC_CREAT | PERMS);
    sem3 = (sem_t *)shmat(sem_id3, NULL, 0);
    sem_init(sem, 1, 1);
    sem_init(sem2, 1, 1);
    sem_init(sem3, 1, 1);
    if (fork() == 0)
    {
        if (fork() == 0)
        {
            
            sem_wait(sem);
            printf("process 1: la ressource 1 est bloqué\n");
            sleep(1);
            printf("process 1: je veux accéder a la ressource 2\n");
            sem_wait(sem2);
            //critical section
            sem_post(sem);
            sem_post(sem2);
        }
        else
        {
            sem_wait(sem2);
            printf("process 2: la ressource 2 est bloqué\n");
             sleep(1);
             printf("process 2: je veux accéder a la ressource 3\n");
            sem_wait(sem3);
            //critical section
            sem_post(sem2);
            sem_post(sem3);
            wait(NULL);
        }
    }
    else
    {
        sem_wait(sem3);
        printf("process 3: la ressource 3 est bloqué\n");
         sleep(1);
         printf("process 3: je veux accéder a la ressource 1\n");
        sem_wait(sem);
        //critical section
        sem_post(sem3);
        sem_post(sem);
        wait(NULL);
    }
}
