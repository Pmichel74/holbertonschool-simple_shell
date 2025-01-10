#include "main.h"
#include <stdlib.h>
/* betty-style: off */

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
	int status = last_status;
	int parsed_status;

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "%s: 1: exit: too many arguments\n", program_name);
			return (1);
		}

		if (string_to_int(args[1], &parsed_status) == -1)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", program_name, args[1]);
			return (2);
		}

		/* Handle negative numbers and ensure proper modulo */
		if (parsed_status < 0)
		{
			status = (256 - (-parsed_status % 256)) % 256;
		}
		else
		{
			status = parsed_status % 256;
		}
	}

	return (status);
}
