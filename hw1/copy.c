#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
void copy(int count, char *buf, int source_fd, int dest_fd);
int main(int argc, char *argv[])
{
    int source_fd, dest_fd, count; //Define the source file descriptor, define the destination file descriptor, the read and write count.
    char buf[BUFFER_SIZE];

    /* Determine parameters*/
    if (argc != 3)
    {
        printf("usage: ./copy <source file> <destination file>\n");
        return -1;
    }
    else if (argc == 3 && (strcmp(argv[1], argv[2]) != 0))
    {
        source_fd = open(argv[1], O_RDONLY);               //Open the source file in read-only mode, where argv[1] stores the path name of the source file
        dest_fd = open(argv[2], O_WRONLY | O_CREAT, 0755); //Open the source file in read and write mode, where the path name of the destination file is stored in argv[2], create the target file if it doesn't exist.
                                                           /* Determine if the opening was successful*/
        if (source_fd == -1 || dest_fd == -1)
        {
            printf("File can not be opend\n");
            return -1;
        }
        copy(count, buf, source_fd, dest_fd);
        close(source_fd);
        close(dest_fd);
    }
    else if (argc == 3 && (strcmp(argv[1], argv[2]) == 0))
    {
        printf("The source file and the destination file cannot be the same!\n"); //Determine whether the source file and destination file are the same
        return -1;
    }

    return 0;
}

void copy(int count, char *buf, int source_fd, int dest_fd)
{
    /* Read the source file data, each time the actual number of bytes read and write is returned to the count, data is stored in the buf*/
    /* write data*/
    do
    {
        memset(buf, 0, sizeof(buf));
        count = read(source_fd, buf, sizeof(buf));
        if (count > 0)
            write(dest_fd, buf, count);
    } while (count > 0);
}
