#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
void readDataFromPipe(int count, char *buf, int pipefd, int fd);
void readDataFromSource(int count, char *buf, int pipefd, int fd);
int main(int argc, char *argv[])
{
    int source_fd, dest_fd, count; //Define the source file descriptor, define the destination file descriptor, the read and write count.
    char buf[BUFFER_SIZE];
    pid_t childpid;
    int pipefd[2];//pipefd[0] for read, pipefd[1] for write
    pipe(pipefd);
    source_fd = open(argv[1], O_RDONLY);               //Open the source file in read-only mode, where argv[1] stores the path name of the source file
    dest_fd = open(argv[2], O_WRONLY | O_CREAT, 0755); //Open the source file in read and write mode, where the path name of the destination file is stored in argv[2], create the target file if it doesn't exist.

    /* Determine parameters*/
    if (argc != 3)
    {
        printf("usage: ./copy <source file> <destination file>\n");
        exit(1);
    }
    else if (argc == 3 && (strcmp(argv[1], argv[2]) != 0))
    {
        /* Determine if the opening was successful*/
        if (source_fd < 0)
        {
            perror("Open source file argv[1] failed.");
            exit(1);
        }

        /* Determine if the opening was successful*/
        if (dest_fd < 0)
        {
            perror("Open target file argv[2] failed.");
            close(source_fd);
            exit(1);
        }

        childpid = fork();
        /*The child process is working*/
        if (childpid == 0)
        {
            close(pipefd[1]);
            readDataFromPipe(count, buf, pipefd[0], dest_fd);//The child process will read the contents of the pipe and write it to the destination file.
        }
        else
        {
            close(pipefd[0]);
            readDataFromSource(count, buf, pipefd[1], source_fd);//The parent process will read the contents of source file and write it to the pipe.
        }
    }

    else if (argc == 3 && (strcmp(argv[1], argv[2]) == 0))
    {
        printf("The source file and the destination file cannot be the same!\n"); //Determine whether the source file and destination file are the same
        exit(1);
    }

    return 0;
}
/*The child process function*/
void readDataFromPipe(int count, char *buf, int pipefd, int fd)
{
    do
    {
        memset(buf, 0, sizeof(buf));
        count = read(pipefd, buf, sizeof(buf));
        if (count > 0)
            write(fd, buf, count);
    } while (count > 0);
    close(pipefd);
    close(fd);
}
/*The parent process function*/
void readDataFromSource(int count, char *buf, int pipefd, int fd)
{
    do
    {
        memset(buf, 0, sizeof(buf));
        count = read(fd, buf, sizeof(buf));
        if (count > 0)
            write(pipefd, buf, count);
    } while (count > 0);
    close(pipefd);
    close(fd);
    wait(NULL);
}