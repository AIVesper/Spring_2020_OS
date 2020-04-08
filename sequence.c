#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
void sequence(int number);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./sequence <number>\n");
        exit(1);
    }
    if (atoi(argv[1]) <= 0)
    {
        perror("Please enter a number greater than 0 to run the program.");
        exit(1);
    }
    sequence(atoi(argv[1]));
    return 0;
}

void sequence(int number)
{
    pid_t pid; //pid is the value returned by the fork()
    pid = fork();
    /*Child processes is working and then output the value*/
    if (pid == 0)
    {
        printf("%d\n", number);
        while (number != 1)
        {
            if (number % 2 == 0)
            {
                number = number / 2;
            }
            else if (number % 2 == 1)
            {
                number = 3 * (number) + 1;
            }

            printf("%d\n", number);
        }
        /*Child processes is done*/
    }
    else
    {
        wait(NULL);
        /*Parent processes is done*/
    }
}