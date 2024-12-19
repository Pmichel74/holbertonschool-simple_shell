#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

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
		return NULL;
	}

	buffer[strcspn(buffer, "\n")] = '\0';
	return buffer;
}
/**
 * tokenize_command - Splits a command string into an array of tokens
 * @command: The input command string to be tokenized
 *
 * This function takes a single command string and breaks it down into
 * individual tokens (words). It allocates memory for an array of strings,
 * where each string is a token from the original command. The resulting
 * array is NULL-terminated.
 *
 * Return: A pointer to an array of strings containing the tokens,
 *         or NULL if memory allocation fails or the input is invalid
 */
char **tokenize_command(char *command)
{
	char **tokens;

	tokens = (char **)malloc(MAX_ARGS * sizeof(char *));

	if (tokens == NULL)

	return (NULL);

	char *token;
	int i = 0;

	token = strtok(command, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return tokens;
}

/**
 * execute_command - Executes a command with its arguments
 * @args: NULL-terminated array of strings containing the command and its args
 *
 * This function creates a child process using fork() and executes the
 * specified command using execve() in the child process. The parent process
 * waits for the child to complete.
 *
 * Return: void
 */
void execute_command(char **args)
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
		if (execve(args[0], args, environ) == -1)
		{
			printf("./shell: No such file or directory\n");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

int main(void)
{
	char *command;
	char **args;

	while (1)
	{
		command = read_command();

		if (command == NULL)
		{
			printf("\n");
			break;
		}

		if (strlen(command) == 0)
		{
			free(command);
			continue;
		}

		args = tokenize_command(command);
		execute_command(args);
		free(args);
		free(command);
	}

	return 0;
}
