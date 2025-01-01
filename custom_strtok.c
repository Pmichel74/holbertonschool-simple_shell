#include "main.h"

/**
 * custom_strtok - Custom implementation of strtok
 * @str: String to tokenize
 * @delim: Delimiter characters
 *
 * Return: Pointer to next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *token;
	char *token_start;

	if (str != NULL)
		token = str;

	if (token == NULL || *token == '\0')
		return (NULL);

	while (*token && strchr(delim, *token))
		token++;

	if (*token == '\0')
		return (NULL);

	token_start = token;

	while (*token && !strchr(delim, *token))
		token++;

	if (*token)
	{
		*token = '\0';
		token++;
	}

	return (token_start);
}
