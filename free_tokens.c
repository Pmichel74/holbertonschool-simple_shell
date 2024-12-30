#include "main.h"

/**
 * free_tokens - Frees memory allocated for an array of strings
 * @tokens: Pointer to an array of strings (char pointers) to be freed
 *
 * This function iterates through the array of strings, freeing each
 * individual string, and then frees the array itself.
 *
 */

void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}
