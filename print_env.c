#include "main.h"

/**
 * print_env - Prints the current environment variables
 * @envp: Array of strings containing environment variables
 *
 * This function iterates through the envp array and prints each
 * environment variable to the standard output.
 */

void print_env(char *envp[])
{
	int i = 0;

	if (envp == NULL)
	{
		fprintf(stderr, "Error: Environment variables not available\n");
		return;
	}

	while (envp[i] != NULL)
{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
