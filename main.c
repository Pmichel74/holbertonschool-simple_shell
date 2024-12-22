#include "main.h"

/**
 * main - Simple UNIX command line interpreter
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @envp: Environment variables
 *
 * Return: Always 0
 */
int main(int argc, char *argv[], char *envp[])
{
    char *command = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    char *args[2];
    pid_t pid;
    int status;

    (void)argc;
    (void)argv;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        characters = getline(&command, &bufsize, stdin);
        if (characters == -1)
        {
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                free(command);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;

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
            if (execve(args[0], args, envp) == -1)
            {
                perror(args[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (wait(&status) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    free(command);
    return (0);
}
