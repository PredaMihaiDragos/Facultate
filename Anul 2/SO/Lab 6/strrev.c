#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void* reverse(void *str) {
    char *cpy = (char*)str;
    int len = strlen(cpy), i;
    char *ret = malloc(len);
    for(i = 0; i < len; ++i) {
        ret[i] = cpy[len-i-1]; 
    }
    return ret;
}

int main(int argc, char *argv[])
{ 
    char s[100];
    scanf("%s", s);

    pthread_t thr;
    if (pthread_create(&thr, NULL, reverse, s)) {
        perror("Eroare creare thread\n");
        return errno;
    }

    void *res;
    if (pthread_join(thr, &res)) {
        perror("Eroare join thread\n");
        return errno;
    }
    printf("%s", (char*)res);
    free(res);
    return 0;
}