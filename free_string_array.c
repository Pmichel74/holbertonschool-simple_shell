#include "main.h"

/**
 * free_string_array - Frees memory allocated for an array of strings
 * @array: Pointer to array of strings to free
 */
void free_string_array(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
		free(array[i]);

	free(array);
}
