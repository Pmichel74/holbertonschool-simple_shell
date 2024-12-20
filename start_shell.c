#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

/**
 * read_command - Reads a command from standard input
 *
 * Return:  NULL if an error occurs
 *         or if the end of the input stream is reached.
 *
 * Note: The caller is responsible for freeing the returned string.
 */

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	printf("#this_is_a_shell_$ ");
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
 * execute_command - Executes a command with its arguments.
 * The function uses the global environ variable for the environment.
 * @args: NULL-terminated array of strings containing the command and its args.
 * @env: Array of strings containing environment variables.
 *
 * Return: void
 *
 */

void execute_command(char **args, char **env)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("Error:");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("No such file or directory\n");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}
