#include "main.h"

/**
 * main - Main execution loop for the simple shell program
 * @argc: Argument count (unused)
 * @argv: Argument vector
 * @envp: Array of environment variables
 *
 * Return: Always returns 0 (success)
 */
int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;
    int interactive = isatty(STDIN_FILENO);
    int last_status = 0;

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (interactive)
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (strlen(line) == 0)
            continue;

        args = tokenize_command(line);
        if (!args || args[0] == NULL)
        {
            free_args(args);
            continue;
        }

   if (strcmp(args[0], "exit") == 0)
        {
            int exit_status = last_status;

            if (args[1] != NULL)
            {
                int parsed_status;

                if (string_to_int(args[1], &parsed_status) == 0)
                {
                    exit_status = parsed_status;
                }
                else
                {
                    fprintf(stderr, "%s: exit: Illegal number: %s\n", argv[0], args[1]);
                    exit_status = 2;
                }
            }

            free_args(args);
            free(line);
            exit(exit_status);
        }

        last_status = execute_command(args, envp, argv[0]);
        free_args(args);
    }

    free(line);
    return (last_status);
}
