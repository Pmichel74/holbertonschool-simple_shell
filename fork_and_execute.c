#include "main.h"

/**
 * fork_and_execute - Forks a new process and executes a command
 * @command_path: Full path to the command to be executed
 * @args: NULL-terminated array of command arguments
 * @envp: Array of environment variables
 * @program_name: name of program
 *
 * Return: 0 on success, -1 on failure
 */
int fork_and_execute(char *command_path, char **args, char **envp,
char *program_name)
{
	pid_t pid;
	int status;

	if (access(command_path, X_OK) == -1)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("Error: execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
	return (0);
}
