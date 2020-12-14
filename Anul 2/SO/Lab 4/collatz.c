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
	pid_t pid = fork();
	if(pid < 0) {
        return errno;
    }
    if(pid == 0) {
        int n;
        printf("n=");
        scanf("%d", &n);
        printf("%d: ", n);
        collatz(n);
    }
    else {
        pid_t child = wait(NULL);
        printf("Child %d finished.\n", child);
    }
	return 0;
}