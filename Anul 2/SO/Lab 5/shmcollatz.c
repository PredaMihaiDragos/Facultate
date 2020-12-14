#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>

void collatz(int n, char *shm_ptr) {
    if (n == 1) {
        shm_ptr += sprintf(shm_ptr, "1.\n");
        return;
    }
    shm_ptr += sprintf(shm_ptr, "%d ", n);
    if (n % 2) {
        collatz(3*n + 1, shm_ptr);
    }
    else {
        collatz(n/2, shm_ptr);
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

    const char *shm_name = "my_shm";
    const int shm_fd = shm_open(shm_name, O_RDWR | O_CREAT);
    if(shm_fd < 0) {
        perror("Eroare creare memorie");
        return errno;
    }

    const size_t page_size = getpagesize();
    const size_t shm_size = page_size * n;
    if(ftruncate(shm_fd, shm_size) == -1) {
        perror("Eroare alocare memorie");
		shm_unlink(shm_name);
		return errno;
	}

    char *shm_ptr;
    for(int i = 0; i < n; ++i) {
        shm_ptr = mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, i * page_size);
        if(shm_ptr == MAP_FAILED) {
			perror("Eroare impartire memorie");
			shm_unlink(shm_name);
			return errno;
		}

        if(fork() == 0) {
            shm_ptr += sprintf(shm_ptr, "%d: ", v[i]);
            collatz(v[i], shm_ptr);
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0);
        }

        munmap(shm_ptr, page_size);
    }
    for(int i = 0; i < n; ++i) {
        wait(NULL);
    }

    for(int i = 0; i < n; ++i) {
        shm_ptr = mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, i * page_size);
		printf("%s", shm_ptr);
		munmap(shm_ptr, page_size);
	}

    shm_unlink(shm_name);
    printf("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}