#include "main.h"

/**
 * cd_command - Change directory builtin command
 * @args: Arguments array
 * @envp: Environment array
 * @program_name: Shell program name
 * Return: 0 on success, 1 on failure
 */
int cd_command(char **args, char **envp, char *program_name)
{
    char cwd[1024];
    char *dir = NULL;
    char *new_args[3];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (1);

    if (args[1] == NULL)
    {
        dir = _getenv("HOME", envp);
        if (dir == NULL)
        {
            fprintf(stderr, "%s: 1: cd: HOME not set\n", program_name);
            return (1);
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        dir = _getenv("OLDPWD", envp);
        if (dir == NULL)
        {
            fprintf(stderr, "%s: 1: cd: OLDPWD not set\n", program_name);
            return (1);
        }
        printf("%s\n", dir);
    }
    else
        dir = args[1];

    if (chdir(dir) != 0)
    {
        fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program_name, dir);
        return (1);
    }

    new_args[0] = "setenv";
    new_args[1] = "OLDPWD";
    new_args[2] = cwd;
    _setenv(new_args, envp, program_name);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        new_args[1] = "PWD";
        new_args[2] = cwd;
        _setenv(new_args, envp, program_name);
    }

    return (0);
}
