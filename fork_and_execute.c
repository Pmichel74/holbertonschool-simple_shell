#include "main.h"

/**
 * forking_helper - Forks and executes a command
 * @command_path: Full path to the command
 * @args: Array of command arguments
 * @envp: Array of environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int forking_helper(char *command_path, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		free(command_path);
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("Error: execve failed");
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("Error: wait failed");
			free(command_path);
			return (-1);
		}
		free(command_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}
