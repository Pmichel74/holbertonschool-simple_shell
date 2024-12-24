#include "main.h"

/**
 * execute_command - Prepares and executes a command
 * @args: NULL-terminated array of command and its arguments
 * @envp: Array of environment variables
 * @program_name: name of program
 *
 * This function finds the full path of the command using find_command(),
 * then calls fork_and_execute() to run the command. It handles basic
 * error checking and frees allocated memory for the command path.
 */
void execute_command(char **args, char **envp, char *program_name)
{
    char *command_path;
    struct stat st;

    if (!args || !args[0])
        return;

    if (strcmp(args[0], "env") == 0)
    {
        print_env(envp);
        return;
    }

    if (args[0][0] == '/' || args[0][0] == '.')
    {
        /* Chemin absolu ou relatif*/
        if (stat(args[0], &st) == 0 && st.st_mode & S_IXUSR)
        {
            command_path = strdup(args[0]);
        }
        else
        {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
            return;
        }
    }
    else
    {
        command_path = find_command(args[0], envp);
    }

    if (!command_path)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
        return;
    }

	if (fork_and_execute(command_path, args, envp) == -1)
    {
        fprintf(stderr, "%s: 1: %s: %s\n", program_name, args[0], strerror(errno));
    }

    free(command_path);
}
