#include "main.h"

/**
 * main - Main execution loop for the simple shell program
 * @argc: Argument count (unused)
 * @argv: Argument vector
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
	int exit_status;
	int last_status = 0;

	signal(SIGINT, sigint_handler);

	while (1)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		nread = custom_getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) == 0)
			continue;

		args = tokenize_command(line);
		if (!args || args[0] == NULL)
		{
			free_string_array(args);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			exit_status = exit_command(args, argv[0], last_status);

			free_string_array(args);
			free(line);
			exit(exit_status);
		}

		last_status = execute_command(args, envp, argv[0]);
		free_string_array(args);
	}

	free(line);
	return (last_status);
}
