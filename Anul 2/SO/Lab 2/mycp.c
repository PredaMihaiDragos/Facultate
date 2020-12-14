#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char** argv)
{
    if (argc != 3) {
        write(1, "Use 2 arguments!\n", 18);
        return 0;
    }
    int fromFileId = open(argv[1], O_RDONLY);
    if (fromFileId == -1) {
        write(1, "Can't open first file\n", 23);
        return 0;
    }
    int toFileId = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU);
    if (toFileId == -1) {
        printf("Can't open second file. Error id: %d\n", errno);
        return 0;
    }

    int bytes = 0;
    char buffer[1024];
    while ((bytes = read(fromFileId, buffer, 1024)) > 0) {
        int totalBytesWritten = 0, bytesWritten;
        while ((bytesWritten = write(toFileId, buffer + totalBytesWritten, bytes - totalBytesWritten)) > 0) {
            totalBytesWritten += bytesWritten;
        }
        if (totalBytesWritten <= 0) {
            write(1, "Can't write to second file\n", 28);
            return 0;
        }
    }
    if (bytes == -1)
        printf("Can't read first file, error id: %d\n", errno);

    close(fromFileId);
    close(toFileId);

    return 0;
}