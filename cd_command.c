#include "main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * update_env_vars - Update PWD and OLDPWD environment variables
 * @cwd: Current working directory
 * @envp: Environment array
 * @program_name: Shell program name
 * Return: 0 on success, 1 on failure
 */
static int update_env_vars(char *cwd, char **envp, char *program_name)
{
	char *new_args[3] = {"setenv", NULL, NULL};

	/* Update OLDPWD */
	new_args[1] = "OLDPWD";
	new_args[2] = cwd;
	_setenv(new_args, envp, program_name);

	/* Update PWD */
	if (getcwd(cwd, sizeof(cwd)))
	{
		new_args[1] = "PWD";
		new_args[2] = cwd;
		_setenv(new_args, envp, program_name);
	}

	return (0);
}

/**
 * get_target_dir - Get target directory for cd command
 * @args: Command arguments
 * @envp: Environment array
 * @program_name: Shell program name
 * Return: Target directory or NULL on failure
 */
static char *get_target_dir(char **args, char **envp, char *program_name)
{
	char *dir = NULL;

	if (!args[1])
	{
		dir = _getenv("HOME", envp);
		if (!dir)
		{
			fprintf(stderr, "%s: 1: cd: HOME not set\n", program_name);
			return (NULL);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		dir = _getenv("OLDPWD", envp);
		if (!dir)
		{
			fprintf(stderr, "%s: 1: cd: OLDPWD not set\n", program_name);
			return (NULL);
		}
		printf("%s\n", dir);
	}
	else
	{
		dir = args[1];
	}

	return (dir);
}

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
	char cwd[1024], *dir;

	/* Get current directory */
	if (!args || !getcwd(cwd, sizeof(cwd)))
		return (1);

	/* Get target directory */
	dir = get_target_dir(args, envp, program_name);
	if (!dir)
		return (1);

	/* Change directory */
	if (chdir(dir) == -1)
	{
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", program_name, dir);
		return (1);
	}

	/* Update environment variables */
	return (update_env_vars(cwd, envp, program_name));
}
