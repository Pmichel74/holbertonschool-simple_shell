#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

extern char **environ;

/**
 * main - Simple UNIX command line interpreter
 *
 * This program implements a basic UNIX shell that can:
 * - Display a prompt and wait for user input
 * - Execute simple, single-word commands
 * - Handle errors and "end of file" condition
 * - Use execve to run commands
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[2];
    pid_t pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;

        args[0] = command;
        args[1] = NULL;

        pid = fork();
        if (pid == -1)
        {
            write(STDERR_FILENO, "Error\n", 6);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                write(STDERR_FILENO, "Error\n", 6);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (wait(&status) == -1)
            {
                write(STDERR_FILENO, "Error\n", 6);
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
