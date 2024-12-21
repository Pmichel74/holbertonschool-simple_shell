#include "main.h"

/**
 * fork_and_execute - Forks a new process and executes a command
 * @command_path: Full path to the command to be executed
 * @args: NULL-terminated array of command arguments
 * @envp: Array of environment variables
 *
 * This function creates a child process using fork(), then uses execve()
 * to replace the child process with the specified command. The parent
 * process waits for the child to complete.
 */

void fork_and_execute(char *command_path, char **args, char **envp)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("Error: fork failed");
		return;
	}

	if (pid == 0)
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}

	else
		wait(&status);
}
