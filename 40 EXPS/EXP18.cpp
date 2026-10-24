#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 3
int buf[SIZE], in = 0, out = 0;
sem_t empty, full;

void *producer(void *a)
{
    for (int i = 1; i <= 6; i++) {
        sem_wait(&empty);
        buf[in] = i;
        printf("Produced %d\n", i);
        in = (in + 1) % SIZE;
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *a)
{
    for (int i = 1; i <= 6; i++) {
        sem_wait(&full);
        printf("Consumed %d\n", buf[out]);
        out = (out + 1) % SIZE;
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}