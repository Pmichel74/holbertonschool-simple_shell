#include "main.h"

/**
 * custom_strtok - Split string into tokens without using strtok
 * @str: String to tokenize
 * @delim: Delimiter string
 *
 * Return: Pointer to next token or NULL if none remain
 */
char *custom_strtok(char *str, char *delim)
{
	static char *last;
	char *start;

	if (str)
		last = str;
	else if (!last)
		return (NULL);

	while (*last && strchr(delim, *last))
		last++;

	if (*last == '\0')
		return (NULL);

	start = last;

	while (*last && !strchr(delim, *last))
		last++;

	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;

	return (start);
}
