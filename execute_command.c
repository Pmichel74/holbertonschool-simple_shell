#include "main.h"
#include <sys/stat.h>
#include <errno.h>

int forking_helper(char *command_path, char **args, char **envp);

/**
 * execute_command - Executes a command with given arguments
 * @args: Array of command arguments
 * @envp: Array of environment variables
 * @program_name: Name of the shell program
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char **envp, char *program_name)
{
	char *command_path = NULL;
	struct stat st;

	if (!args || !args[0])
		return (-1);

	if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		return (0);
	}

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && st.st_mode & S_IXUSR)
			command_path = strdup(args[0]);
	}
	else
		command_path = find_command(args[0], envp);

	if (!command_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (-1);
	}

	return (forking_helper(command_path, args, envp));
}

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
