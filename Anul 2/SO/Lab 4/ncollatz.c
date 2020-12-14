#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void collatz(int n) {
    if (n == 1) {
        printf("1.\n");
        return;
    }
    printf("%d ", n);
    if (n % 2) {
        collatz(3*n + 1);
    }
    else {
        collatz(n/2);
    }
}

int main(int argc, char** argv)
{
    int n;
    printf("n=");
    scanf("%d", &n);
    int *v = malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
    }
    printf("Parent %d\n", getpid());
    for(int i = 0; i < n; ++i) {
        if(fork() == 0) {
            printf("%d: ", v[i]);
            collatz(v[i]);
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0);
        }
    }
    for(int i = 0; i < n; ++i) {
        wait(NULL);
    }
    printf("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}