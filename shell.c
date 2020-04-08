#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_LINE 80 /* The maximum length command */
char *cmdHistory = "no commands";

void addToHistory(char *command)
{
    cmdHistory = strdup(command); //Copy the command and stores it in the cmdHistory
}

void runCMD(char *command, char *params[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed\n");
    }
    else if (pid == 0) //Child Process
    {
        execvp(command, params);
        exit(1);
    }
    wait(NULL);
}

void commandParse(char *buf, char **args)
{
    addToHistory(buf);
    int argc = 0;
    int status = 0;
    for (int i = 0; buf[i] != 0; ++i)
    {
        if (status == 0 && !isspace(buf[i]))
        {
            args[argc++] = buf + i;
            status = 1;
        }
        else if (isspace(buf[i]))
        {
            status = 0;
            buf[i] = 0;
        }
    }
    args[argc] = NULL;
    runCMD(buf, args);
}

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char buf[BUFFER_SIZE];
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        /**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) parent will invoke wait() unless command included &
*/
        memset(buf, 0x00, sizeof(buf));
        while (scanf("%[^\n]%*c", buf) == 0)
        { //0 means that only line feeds were entered.
            printf("You only entered one line break.");
            while (getchar() != '\n')
                ;
        }
        if (strcmp("!!", buf) == 0)
        {
            if (strcmp("no commands", cmdHistory) == 0)
            {
                printf("No commands in history.\n");
            }
            else
            {
                commandParse(cmdHistory, args);
            }
        }
        else
        {
            commandParse(buf, args);
        }
    }
}
