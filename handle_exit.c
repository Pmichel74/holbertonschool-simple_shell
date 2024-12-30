#include "main.h"

/**
 * handle_exit - Quitte le shell avec le code de statut donné.
 * @args: array of strings containing the command and its arguments.
 *
 * Return: always return 0 for successful execution
 */
int handle_exit(char **args)
{
	if (args[1] != NULL)
	{
		char *endptr;
		long status = strtol(args[1], &endptr, 10);
	/*	status = _atoi(args[1]); */

		/*exit(status);*/
		if (*endptr != '\0')
		{
			fprintf(stderr, "Usage: exit status\n");
			return (1);
		}
		exit((int)status);
	}
	exit(0);
}
