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
 * tokenize_command - Splits a command string into an array of tokens
 * @command: The input command string to be tokenized
 *
 * This function takes a single command string and breaks it down into
 * individual tokens (words).
 *
 * Return: A pointer to an array of strings containing the tokens,
 *        or NULL if memory allocation fails or the input is invalid
 */
char **tokenize_command(char *command)
{
	char **tokens;

	tokens = (char **)malloc(MAX_ARGS * sizeof(char *));

	if (tokens == NULL)

	return (NULL);

	char *token;
	int i = 0;
	int j;

	if (!tokens)
	{
		perror("malloc failed");
		return (NULL);
	}

	token = strtok(command, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("strdup failed");

			for (j = 0; j < i; j++)
				free(tokens[j]);
			free(tokens);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * free_tokens - Frees memory allocated for an array of strings
 * @tokens: Pointer to an array of strings (char pointers) to be freed
 *
 * This function iterates through the array of strings, freeing each
 * individual string, and then frees the array itself.
 * the tokenize_command function is NULL.
 *
 * Return: void
 *
 */
void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}

/**
 * execute_command - Executes a command with its arguments.
 * The function uses the global environ variable for the environment.
 * @args: NULL-terminated array of strings containing the command and its args
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

/**
 * main - Entry point for the simple shell program
 * @argc: The argument count (unused)
 * @argv: The argument vector (unused)
 *
 * Return: Always returns 0 (success)
 *
 */
int main(int argc, char *argv[])
{
	char *command = NULL;
	char **args = NULL;
	char **env = argv + 1;

	(void)argc;/*Turn off warnings*/

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
		if (args)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_tokens(args);
				free(command);
				exit(0);
			}
			execute_command(args, env);
			free_tokens(args);
		}
		free(command);

	}
	return (0);
}
