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
	if (strcmp(args[0], "setenv") == 0)
		return (_setenv(args, envp, program_name));
	if (strcmp(args[0], "unsetenv") == 0)
		return (_unsetenv(args, envp, program_name));

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
