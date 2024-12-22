#include "main.h"

/**
 * read_command - Reads a command from standard input
 *
 * This function prompts the user with a shell prompt, then reads a line
 * of input using getline(). It removes the trailing newline character
 * if present.
 *
 * Return: A dynamically allocated string containing the command,
 *         or NULL if an error occurs or end-of-file is reached.
 */

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	printf("#my_simple_shell_$ ");
	fflush(stdout);

	characters = getline(&buffer, &bufsize, stdin);

	if (characters == -1)
	{
		free(buffer);
		return (NULL);
	}

	buffer[strcspn(buffer, "\n")] = '\0';
	return (buffer);
}

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
