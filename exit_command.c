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
	long parsed_status;
	char *endptr;

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "%s: 1: exit: too many arguments\n", program_name);
			return (1);
		}

		errno = 0;
		parsed_status = strtol(args[1], &endptr, 10);

		if (*endptr != '\0' || errno == ERANGE ||
			parsed_status > 255 || parsed_status < 0)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
					program_name, args[1]);
			exit(2);
		}
		exit_status = (int)parsed_status;
	}

	exit(exit_status);
}
