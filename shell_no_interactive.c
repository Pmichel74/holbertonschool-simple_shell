#include "shell.h"
/**
 * shell_no_interactive - unix command line interpreter
 *
 * Return: void
 */
void shell_no_interactive(void)
{
	char *line;
	char **args;
	int status = -1;

	do {
		line = read_stream();
		args = split_line(line);
		status = execute_args(args);
		free(line);
		free(args);

		if (status >= 0)
			exit(status);
	} while (status == -1);
}
