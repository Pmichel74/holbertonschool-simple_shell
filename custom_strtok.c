#include "main.h"

/**
 * is_delim - Check if character is delimiter
 * @c: Character to check
 * @delim: String of delimiters
 * Return: 1 if delimiter, 0 if not
 */
static int is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * custom_strtok - tokenize a string
 * @str: string to tokenize
 * @delim: delimiter characters
 * Return: pointer to next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *saved_ptr;
	char *start;

	if (str != NULL)
		saved_ptr = str;
	else if (saved_ptr == NULL)
		return (NULL);

	/* Skip leading delimiters */
	while (*saved_ptr && is_delim(*saved_ptr, delim))
		saved_ptr++;

	if (*saved_ptr == '\0')
	{
		saved_ptr = NULL;
		return (NULL);
	}

	start = saved_ptr;

	/* Find end of token */
	while (*saved_ptr && !is_delim(*saved_ptr, delim))
		saved_ptr++;

	if (*saved_ptr)
	{
		*saved_ptr = '\0';
		saved_ptr++;
	}

	return (start);
}
