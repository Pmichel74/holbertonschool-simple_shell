#include "main.h"

/**
 * find_command - Searches for a command in PATH or as absolute/relative path
 * @command: Name of the command to search for
 * @envp: Array of environment variables
 *
 * Return: Full path of the command if found, NULL otherwise
 */
char *find_command(char *command, char *envp[])
{
	char *path;
	char *absolute_path;

	if (!command)
		return (NULL);

	absolute_path = check_absolute_path(command);
	if (absolute_path)
		return (absolute_path);

	path = find_path(envp);
	if (!path)
		return (NULL);

	absolute_path = search_in_path(command, path);
	if (!absolute_path)
		return (NULL);

	free(path);
	return (absolute_path);
}
