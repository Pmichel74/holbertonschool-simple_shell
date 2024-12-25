#include "main.h"

/**
 * read_command - Reads a command from standard input
 *
 * This function prompts the user with a shell prompt, then reads a line
 * of input using getline(). It removes the trailing newline character
 * if present.
 *
 * Return: A dynamically allocated string containing the command,
 *         or NULL if an error occurs or end-of-file is reached.
 */

char *read_command(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	printf("#my_simple_shell_$ ");
	fflush(stdout);

	characters = getline(&buffer, &bufsize, stdin);

	if (characters == -1)
	{
		free(buffer);
		return (NULL);
	}

	buffer[strcspn(buffer, "\n")] = '\0';
	return (buffer);
}
