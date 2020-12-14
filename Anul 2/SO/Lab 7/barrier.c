#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

#define NTHRS 5

sem_t sem;
pthread_mutex_t mtx;
int S = 0;

int barrier_point()
{
    int _S, i;
    pthread_mutex_lock(&mtx);
    S++;
    _S = S;
    pthread_mutex_unlock(&mtx);

    if(_S < NTHRS) {
        if(sem_wait(&sem)) {
            perror("Eroare wait semafor.");
            return errno;
        }
    }
    else {
        for(i = 0; i < NTHRS; ++i) {
            if(sem_post(&sem)) {
                perror("Eroare post semafor");
                return errno;
            }
        }
    }
    return 0;
}

void *tfun(void *v)
{
	int *tid = (int*)v;

	printf("%d reached the barrier \n", *tid);
	barrier_point();
	printf("%d passed the barrier \n", *tid);

	free(tid);
	return NULL;
}


int main()
{
    pthread_t thr[NTHRS];
	int i;

	if(sem_init(&sem, 0, S)) {
        perror("Eroare creare semafor.");
        return errno;
    }

	if(pthread_mutex_init(&mtx, NULL)) {
        perror("Eroare creare mutex.");
        return errno;
    }

	for(i = 0; i < NTHRS; i++) {
        int *k = (int*)malloc(1);
        *k = i;
		if(pthread_create(&thr[i], NULL, tfun, k)) {
            perror("Eroare creare thread.");
            return errno;
        }
	}

    for(i = 0; i < NTHRS; i++) {
        if(pthread_join(thr[i], NULL)) {
            perror("Eroare join thread.");
            return errno;
        }
    }

    sem_destroy(&sem);
    pthread_mutex_destroy(&mtx);
    return 0;
}
