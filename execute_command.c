#include "main.h"

/**
 * execute_command - Execute a command
 * @args: Command arguments
 * @envp: Environment variables
 * @program_name: Program name
 *
 * Return: Status of command execution
 */

int execute_command(char **args, char **envp, char *program_name)
{
    char *command_path = NULL;
    struct stat st;
    int result;

    if (!args || !args[0])
        return (-1);

    if (strcmp(args[0], "env") == 0)
    {
        print_env(envp);
        return (0);
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
        if (!args[1] || !args[2])
        {
            fprintf(stderr, "%s: Usage: setenv VARIABLE VALUE\n", program_name);
            return (1);
        }
        return (_setenv(args[1], args[2], envp) == 0 ? 0 : 1);
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        if (!args[1])
        {
            fprintf(stderr, "%s: Usage: unsetenv VARIABLE\n", program_name);
            return (1);
        }
        return (_unsetenv(args[1], envp) == 0 ? 0 : 1);
    }

    if (args[0][0] == '/' || args[0][0] == '.')
    {
        if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
            command_path = strdup(args[0]);
        else
        {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
            return (127);
        }
    }
    else
    {
        command_path = find_command(args[0], envp);
        if (!command_path)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
            return (127);
        }
    }

    result = fork_and_execute(command_path, args, envp, program_name);
    free(command_path);
    return (result);
}
