#include "main.h"

/**
 * free_args - Frees the memory allocated for command arguments
 * @args: The array of command arguments to be freed
 *
 * This function frees each individual argument string and then
 * frees the array itself.
 */

void free_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}
