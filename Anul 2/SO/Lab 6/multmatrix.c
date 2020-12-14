#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int **first, **second, **res;
int n, m, p;
struct elem
{
    int x, y;
};

void *mult_elem(void *elem) {
    struct elem *e = elem;
    int i;
    res[e->x][e->y] = 0;
    for(i = 0; i < m; ++i) {
        res[e->x][e->y] += first[e->x][i] * second[i][e->y];
    }
    return &res[e->x][e->y];
}

int main(int argc, char *argv[])
{
    int k, i, j;
    scanf("%d %d", &n, &m);
    first = malloc(sizeof(int*) * n);
    for(i = 0; i < n; ++i) {
        first[i] = malloc(sizeof(int) * m);
        for(j = 0; j < m; ++j) {
            scanf("%d", &first[i][j]);
        }
    }

    scanf("%d %d", &k, &p);
    second = malloc(sizeof(int*) * k);
    for(i = 0; i < k; ++i) {
        second[i] = malloc(sizeof(int) * p);
        for(j = 0; j < p; ++j) {
            scanf("%d", &second[i][j]);
        }
    }
    if(m != k) {
        printf("Dimensiuni incompatibile ale matricilor.");
        return 0;
    }

    pthread_t thr[n][p];
    res = malloc(sizeof(int*) * n);
    for(i = 0; i < n; ++i) {
        res[i] = malloc(sizeof(int) * p);
        for(j = 0; j < p; ++j) {
            struct elem *e = malloc(sizeof(struct elem));
            e->x = i;
            e->y = j;
            if (pthread_create(&thr[i][j], NULL, mult_elem, e)) {
                perror("Eroare creare thread\n");
                return errno;
            }
        }
    }

    for(i = 0; i < n; ++i) {
        for(j = 0; j < p; ++j) {
            void *temp;
            if (pthread_join(thr[i][j], temp)) {
                perror("Eroare join thread\n");
                return errno;
            }
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}