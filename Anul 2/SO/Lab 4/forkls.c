#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0) {
        return errno;
    }
    if(pid == 0) {
        printf("Child PID=%d\n", getpid());
        char *argv[] = {"", NULL};
        execve("/bin/ls", argv, NULL);
    }
    else {
        pid_t child = wait(NULL);
        printf("Child %d finished.\n", child);
        printf("My PID=%d\n", getpid());
    }
	return 0;
}