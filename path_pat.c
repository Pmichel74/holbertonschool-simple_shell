#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * _get_path - get jiable PATH.
 * @env: enviromente local
 * Return: value of PATH.
 */

char *_get_path(char **env)
{
	size_t i = 0, total_char = 5, j = 5;
	char *path = NULL;

	/*looking for PATH*/
	for (i = 0; strncmp(env[i], "PATH=", 5); i++)
		;
	if (!env[i])
	return (NULL);

	/*count chars for PATH*/
	for (total_char = 5; env[i][j] != '\0'; j++, total_char++)
		;

	path = MALLOC(sizeof(char) * (total_char) + 1)

	if (!PATH)
	return (NULL);

	/*copy PATH value in new string*/
	for (total_char = 5; j = 0; env[i][total_char] != '\0'; j++, total_char++)
	path[j] = env[i][total_char];

	path[j] = '\0';
}
