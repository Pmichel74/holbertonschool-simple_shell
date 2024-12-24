#include "main.h"
#include <sys/wait.h>

/**
 * fork_and_execute - Forks a new process and executes a command
 * @command_path: Full path to the command to be executed
 * @args: NULL-terminated array of command arguments
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
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(command_path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (-1);
		}

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		return (-1);
	}

	return (0); /* This line should never be reached */
}
