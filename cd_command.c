#include "main.h"

/**
 * cd_command - Change current directory
 * @args: Arguments array
 * @program_name: Shell program name
 * Return: 0 on success, 1 on failure
 */
int cd_command(char **args, char *program_name)
{
    char *dir, *oldpwd;
    char current[PATH_MAX];

    if (!getcwd(current, PATH_MAX))
        return (1);

    if (!args[1]) /* cd with no args */
    {
        dir = getenv("HOME");
        if (!dir)
        {
            fprintf(stderr, "%s: 1: cd: HOME not set\n", program_name);
            return (1);
        }
    }
    else if (strcmp(args[1], "-") == 0) /* cd - */
    {
        dir = getenv("OLDPWD");
        if (!dir)
        {
            fprintf(stderr, "%s: 1: cd: OLDPWD not set\n", program_name);
            return (1);
        }
        printf("%s\n", dir);
    }
    else
        dir = args[1];

    oldpwd = strdup(current);
    if (!oldpwd)
        return (1);

    if (chdir(dir) == -1)
    {
        fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program_name, dir);
        free(oldpwd);
        return (1);
    }

    if (getcwd(current, PATH_MAX) != NULL)
    {
        setenv("OLDPWD", oldpwd, 1);
        setenv("PWD", current, 1);
    }

    free(oldpwd);
    return (0);
}
