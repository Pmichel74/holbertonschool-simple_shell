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
	int i = 0;
	long number = 0;

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "%s: 1: exit: too many arguments\n", program_name);
			return (1);
		}

		/* Handle negative numbers */
		if (args[1][0] == '-')
			i = 1;

		/* Validate and convert string to number */
		while (args[1][i] != '\0')
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
				program_name, args[1]);
				exit(2);
			}
			number = number * 10 + (args[1][i] - '0');
			i++;
		}

		/* Apply negative sign if needed */
		if (args[1][0] == '-')
			number = -number;

		exit_status = number % 256;
		if (exit_status < 0)
			exit_status += 256;
	}

	exit(exit_status);
}