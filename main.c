#include "main.h"

/**
 * main - Entry point for the simple shell program
 * @argc: The argument count (unused)
 * @argv: The argument vector (unused)
 * @envp: Array of environment variables
 *
 * Return: Always returns 0 (success)
 */

int main(int argc, char *argv[], char *envp[])
{
	char *command = NULL;
	char **args;
	int should_exit = 0;

	(void)argc;

	while (!should_exit)
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
		if (!args)
		{
			free(command);
			continue;
		}
		if (args[0] == NULL)
		{
			free_args(args);
			free(command);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
			should_exit = 1;
		else
			execute_command(args, envp, argv[0]);
		free_args(args);
		free(command);
	}
	return (0);
}
