#include "main.h"

/**
 * execute_command - Prepares and executes a command
 * @args: NULL-terminated array of command and its arguments
 * @envp: Array of environment variables
 *
 * This function finds the full path of the command using find_command(),
 * then calls fork_and_execute() to run the command. It handles basic
 * error checking and frees allocated memory for the command path.
 */

void execute_command(char **args, char **envp)
{
	char *command_path;

	if (!args || !args[0])
		return;

	if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		return;
	}

	command_path = find_command(args[0], envp);

	if (!command_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return;
	}
	fork_and_execute(command_path, args, envp);
	free(command_path);
}
