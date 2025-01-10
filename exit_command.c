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
	 int exit_status = last_status;
     int i, len_of_int = 10;
    unsigned int num = 0;
    unsigned int max = 1 << (sizeof(int) * 8 - 1);

	if (!args || !args[0])
		return (-3);

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "%s: 1: exit: too many arguments\n", program_name);
			return (1);
		}

		/* Handle '+' prefix */
		i = (args[1][0] == '+') ? 1 : 0;
		if (args[1][0] == '+')
			len_of_int++;

		 /* Validate number and check overflow */
		while (args[1][i])
		{
			if (i <= len_of_int && args[1][i] >= '0' && args[1][i] <= '9')
				num = (num * 10) + (args[1][i] - '0');
			else
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", program_name, args[1]);
				return (2);
			}
			i++;
		}

		if (num > max - 1)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", program_name, args[1]);
			return (2);
		}

		exit_status = num % 256;
	}

	return (exit_status);
}
