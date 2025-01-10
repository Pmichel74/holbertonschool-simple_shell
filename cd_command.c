#include "main.h"

/**
 * cd_command - Change directory builtin command
 * @args: Arguments array
 * @program_name: Shell program name
 * Return: 0 on success, 1 on failure
 */
int cd_command(char **args, char *program_name)
{
    char cwd[1024];
    char *dir = NULL;

    /* Save current directory for OLDPWD */
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (1);

    /* Handle cd with no arguments */
    if (args[1] == NULL)
    {
        dir = getenv("HOME");
        if (dir == NULL)
        {
            fprintf(stderr, "%s: 1: cd: HOME not set\n", program_name);
            return (1);
        }
    }
    /* Handle cd - */
    else if (strcmp(args[1], "-") == 0)
    {
        dir = getenv("OLDPWD");
        if (dir == NULL)
        {
            fprintf(stderr, "%s: 1: cd: OLDPWD not set\n", program_name);
            return (1);
        }
        printf("%s\n", dir);
    }
    else
        dir = args[1];

    /* Change directory */
    if (chdir(dir) != 0)
    {
        fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program_name, dir);
        return (1);
    }

    /* Update environment variables */
    setenv("OLDPWD", cwd, 1);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        setenv("PWD", cwd, 1);

    return (0);
}
