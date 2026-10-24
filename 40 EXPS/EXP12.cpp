#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t chopstick[N];

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    printf("Philosopher %d is thinking\n", i);
    sleep(1);

    if (i == N - 1) {              /* last one picks in reverse order: avoids deadlock */
        sem_wait(&chopstick[(i + 1) % N]);
        sem_wait(&chopstick[i]);
    } else {
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i + 1) % N]);
    }

    printf("Philosopher %d is eating\n", i);
    sleep(1);

    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i + 1) % N]);
    printf("Philosopher %d finished eating\n", i);
    return NULL;
}

int main()
{
    pthread_t t[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);
    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    return 0;
}