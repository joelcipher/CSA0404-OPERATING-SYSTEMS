#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, mutex;
int data = 0, readcount = 0;

void *writer(void *a)
{
    sem_wait(&wrt);
    data++;
    printf("Writer wrote %d\n", data);
    sem_post(&wrt);
    return NULL;
}

void *reader(void *a)
{
    sem_wait(&mutex);
    if (++readcount == 1) sem_wait(&wrt);   /* first reader blocks writers */
    sem_post(&mutex);

    printf("Reader read %d\n", data);

    sem_wait(&mutex);
    if (--readcount == 0) sem_post(&wrt);   /* last reader releases writers */
    sem_post(&mutex);
    return NULL;
}

int main()
{
    pthread_t r[3], w[2];
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, NULL);
    for (int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    return 0;
}