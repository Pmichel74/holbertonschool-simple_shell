#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[2];
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\n");
            break;  /* Handle "end of file" condition (Ctrl+D) */
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;  /* Empty command, show prompt again */

        args[0] = command;
        args[1] = NULL;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            if (execve(args[0], args, NULL) == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            if (wait(&status) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
