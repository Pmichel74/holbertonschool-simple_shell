#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

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

char **tokenize_command(char *command)
{
	char **tokens = malloc(MAX_ARGS * sizeof(char *));
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

void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}

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

int main(int argc, char *argv[])
{
	char *command = NULL;
	char **args = NULL;
	char **env = argv + 1;

	(void)argc;

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
