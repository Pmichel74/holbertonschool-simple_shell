#include "main.h"

/**
 * cd_command - Change current directory of the shell
 * @args: Array of command arguments (args[1] = directory)
 * @envp: Array of environment variables
 * @program_name: Name of shell program for error messages
 *
 * Description: Changes the current working directory:
 * - No args: changes to HOME directory
 * - "-": changes to previous directory (OLDPWD)
 * - Otherwise: changes to specified directory
 * Updates PWD and OLDPWD environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int cd_command(char **args, char **envp, char *program_name)
{
    char cwd[1024], *dir = NULL;
    char *new_args[3] = {"setenv", NULL, NULL};

    if (!args || !getcwd(cwd, sizeof(cwd)))
        return (1);

    if (!args[1])
    {
        dir = _getenv("HOME", envp);
        if (!dir)
        {
            fprintf(stderr, "%s: 1: cd: HOME not set\n", program_name);
            return (1);
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        dir = _getenv("OLDPWD", envp);
        if (!dir)
        {
            fprintf(stderr, "%s: 1: cd: OLDPWD not set\n", program_name);
            return (1);
        }
        printf("%s\n", dir);
    }
    else
        dir = args[1];

    if (chdir(dir) == -1)
    {
        fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program_name, dir);
        return (1);
    }

    new_args[1] = "OLDPWD";
    new_args[2] = cwd;
    _setenv(new_args, envp, program_name);

    if (getcwd(cwd, sizeof(cwd)))
    {
        new_args[1] = "PWD";
        new_args[2] = cwd;
        _setenv(new_args, envp, program_name);
    }

    return (0);
}
