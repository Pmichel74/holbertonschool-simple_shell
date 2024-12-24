#include "main.h"

/**
 * main - Entry point for the simple shell program
 * @argc: The argument count (unused)
 * @argv: The argument vector (unused)
 * @envp: Array of environment variables
 *
 * Return: Always returns 0 (success)
 */
int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strlen(line) == 0)
			continue;
		args = tokenize_command(line);
		if (!args || args[0] == NULL)
		{
			free_args(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			int exit_status = lsh_exit(args);

			free(line);
			exit(exit_status);
		}
		execute_command(args, envp, argv[0]);
		free_args(args);
	}
	free(line);
	return (0);
}
