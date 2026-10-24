#include <stdio.h>
#include <pthread.h>

void *print_msg(void *arg)
{
    int id = *(int *)arg;
    for (int i = 1; i <= 3; i++)
        printf("Thread %d: iteration %d\n", id, i);
    return NULL;
}

int main()
{
    pthread_t t[3];
    int id[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, print_msg, &id[i]);
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    printf("All threads finished.\n");
    return 0;
}