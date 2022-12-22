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
    int sem_id;
    sem_t *sem;
    sem_id = shmget(KEY + 1, sizeof(sem_t), IPC_CREAT | PERMS);
    sem = (sem_t *)shmat(sem_id, NULL, 0);
    sem_init(sem, 1, 1);
    if (fork() == 0)
    {
        if (fork() == 0)
        {

            sem_wait(sem);

            system("firefox");
            printf("firefox lancé\n");
            sem_post(sem);
        }
        else
        {
            sem_wait(sem);
            system("libreoffice");
            printf("libre office lancé\n");
            sem_post(sem);
            wait(NULL);
        }
    }
    else
    {
        sem_wait(sem);
        system("opera");
        printf("lopéra lancé\n");
        sem_post(sem);
        wait(NULL);
    }
}
