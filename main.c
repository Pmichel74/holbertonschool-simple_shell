#include "main.h"
#include <libgen.h>

/**
 * main - Main execution loop for the simple shell program.
 * @argc: Argument count (unused).
 * @argv: Argument vector.
 * @envp: Array of environment variables.
 *
 * Return: Always returns 0 (success).
 */
int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
    char *command_path;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;
    int interactive = isatty(STDIN_FILENO);
    int status;

    while (1)
    {
        if (interactive)
        {
            /* Display the prompt in interactive mode */
            printf("$ ");
        }

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (interactive)
            {
                /* Print a newline on EOF in interactive mode */
                printf("\n");
            }
            break;  /* Exit the loop on EOF */
        }

        if (nread > 0 && line[nread - 1] == '\n')
        {
            /* Remove the trailing newline from the input */
            line[nread - 1] = '\0';
        }

        if (strlen(line) == 0)
        {
            /* Ignore empty lines */
            continue;
        }

        /* Tokenize the command line */
        args = tokenize_command(line);
        if (!args || args[0] == NULL)
        {
            free_args(args);
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            /* Handle the "exit" builtin command */
            free_args(args);
            free(line);
            exit(EXIT_SUCCESS);
        }

        /* Find the full path of the command */
        command_path = find_command(args[0], envp);
        if (!command_path)
        {
            /* Command not found */
            fprintf(stderr, "%s: 1: %s: not found\n",
                    basename(argv[0]), args[0]);
            free_args(args);
            continue;
        }

        /* Execute the command */
        status = execute_command(args, envp, argv[0]);
        if (status == -1)
        {
            /* Error executing the command */
            fprintf(stderr, "%s: command execution failed: %s\n",
                    argv[0], args[0]);
        }
        else if (status != 0)
        {
            /* Handle other error codes if necessary */
        }

        /* Free the allocated memory */
        free_args(args);
    }

    free(line);
    return (0);
}
