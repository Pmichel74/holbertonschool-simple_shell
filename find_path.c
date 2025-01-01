#include "main.h"

/**
 * find_path - Searches for the PATH in environment variables
 * @envp: Array of environment variables
 *
 * Return: A string containing the value of PATH, or NULL if not found
 */

char *find_path(char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}
