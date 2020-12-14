#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define MAX_RESOURCES 5
#define NR_THREADS 10
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count)
{
    pthread_mutex_lock(&mtx);
    if(available_resources < count) {
        pthread_mutex_unlock(&mtx);
        return -1;
    }
    else {
        available_resources -= count;
        printf("Got %d resources, %d remaining\n", count, available_resources);
    }
    pthread_mutex_unlock(&mtx);
    return 0;
}
int increase_count(int count)
{
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Release %d resources, %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mtx);
    return 0;
}
void *functie(void *c)
{
    int* count = (int*)c;
    if (decrease_count(*count) != -1)
        increase_count(*count);
    return 0;
}

int main()
{
    if(pthread_mutex_init(&mtx, NULL)) {
          perror("Eroare creare mutex.");
          return errno;
    }

    pthread_t id[NR_THREADS];
    int *count[NR_THREADS];
    int i;
    
    for(i=0; i < NR_THREADS; i++) {
        count[i] = malloc(sizeof(int));
        *count[i] = rand() % (MAX_RESOURCES + 1);
        if(pthread_create(&id[i], NULL, functie, count[i])) {
            perror("Eroare create thread.");
            return errno;
        }
    }

    for(i=0; i < NR_THREADS; i++) {
        if(pthread_join(id[i], NULL)) {
            perror("Eroare join thread.");
            return errno;
        }
        free(count[i]);
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}
