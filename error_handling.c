#include "main.h"

/**
 * print_error - Print error message in the required format
 * @prog_name: Name of the program (argv[0])
 * @cmd: Command that caused the error
 */
void print_error(char *prog_name, char *cmd)
{
	char error_message[100];

	snprintf(error_message, sizeof(error_message),
		 "%s: 1: %s: not found\n", prog_name, cmd);
	write(STDERR_FILENO, error_message, strlen(error_message));
}
