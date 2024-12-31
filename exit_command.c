#include "main.h"

/**
 * exit_command - Handles the exit command in the shell
 * @args: Array of command arguments
 * @program_name: Name of the shell program
 * @last_status: Last exit status of a command
 *
 * Return: The exit status to be used when exiting the shell
 */

int exit_command(char **args, char *program_name, int last_status)
{
	int exit_status = last_status;
	int parsed_status;

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "%s: exit: too many arguments\n", program_name);
			return (1);
		}

		if (string_to_int(args[1], &parsed_status) == 0)
		{
			exit_status = parsed_status;
		}
		else
		{
			fprintf(stderr, "%s: exit: Illegal number: %s\n", program_name, args[1]);
			exit_status = 2;
		}
	}

	return (exit_status);
}
