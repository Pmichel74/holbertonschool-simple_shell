#include "shell.h"
/**
 * shell_interactive - UNIX command line interpreter
 *
 * Return: void
 */
void shell_interactive(void)
{
	char *line;
	char **args;
	int status = -1;

	do {
		write(STDOUT_FILENO, "simple_shell> ", 14);
		line = read_line();
		args = split_line(line);
		status = execute_args(args);
		free(line);
		free(args);

	} while (status != -2);
}
