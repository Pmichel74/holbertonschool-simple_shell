#include "main.h"

/**
 * fork_and_execute - Forks a new process and executes a command
 * @command_path: Full path to the command to be executed
 * @args: Array of command arguments
 * @envp: Array of environment variables
 *
 * Return: Exit status of the child process, or -1 on failure
 */
int fork_and_execute(char *command_path, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(command_path, args, envp) == -1)
		{
			perror("Error: execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		if (wait(&status) == -1)
		{
			perror("Error: wait failed");
			return (-1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}
