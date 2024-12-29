#include "main.h"
/**
 * handle_exit - Handles the 'exit' built-in command.
 * @args: The arguments passed to the 'exit' command.
 * @prog_name: The name of the shell program.
 *
 * Return: The exit status code.
 */
int handle_exit(char **args, char *prog_name)
{
		int exit_status = 0;

		if (args[1] != NULL)
		{
				char *endptr;
				long val = strtol(args[1], &endptr, 10);

				if (*endptr != '\0' || errno == ERANGE)
				{
						fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
								prog_name, args[1]);
						exit_status = 2;
				}
				else if (val < -2147483648 || val > 2147483647)
				{
						fprintf(stderr, "%s: 1: exit: Illegal number: %s\n",
								prog_name, args[1]);
						exit_status = 2;
				}
				else
				{
						exit_status = (int)val;
				}
		}

		return (exit_status);
}
