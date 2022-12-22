#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;
sem_t sem2;
sem_t sem3;

int result[3];
int i = -1;
int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;

pthread_t thr1, thr2, thr3, thr4;

void *thread1(void *arg)
{
    sem_wait(&sem);
    i++;
    result[i] = a + b;
    printf("a+b = %d\n", result[i]);
    if (i == 1)
    {
        sem_post(&sem2);
    }
    else if (i == 2)
    {
        sem_post(&sem3);
    }
    sem_post(&sem);
}
void *thread2(void *arg)
{
    sem_wait(&sem);
    i++;
    result[i] = c - d;
    printf("c-d = %d\n", result[i]);
    if (i == 1)
    {
        sem_post(&sem2);
    }
    else if (i == 2)
    {
        sem_post(&sem3);
    }
    sem_post(&sem);
}
void *thread3(void *arg)
{
    sem_wait(&sem);
    i++;
    result[i] = e + f;
    printf("e+f = %d\n", result[i]);
    if (i == 1)
    {
        sem_post(&sem2);
    }
    else if (i == 2)
    {
        sem_post(&sem3);
    }
    sem_post(&sem);
}

void *thread4(void *arg)
{
    sem_wait(&sem2);
    int final_result = result[0] * result[1];
    printf("resut[0]*result[1] = %d\n", final_result);
    sem_wait(&sem3);
    final_result = final_result * result[2];
    printf("result of (a+b)*(c-d)*(e+f) = %d\n", final_result);
}
int main()
{
    sem_init(&sem, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    pthread_t thr1, thr2, thr3, thr4;

    pthread_create(&thr1, NULL, thread1, NULL);
    pthread_create(&thr2, NULL, thread2, NULL);
    pthread_create(&thr3, NULL, thread3, NULL);
    pthread_create(&thr4, NULL, thread4, NULL);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);
    pthread_join(thr4, NULL);

    sem_destroy(&sem);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
}