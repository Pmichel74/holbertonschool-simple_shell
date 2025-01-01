#include "main.h"

/**
 * get_env_size - Get size of environment array
 * @envp: Environment array
 * Return: Size of environment array
 */
static int get_env_size(char **envp)
{
	int size = 0;

	while (envp[size])
		size++;
	return (size);
}

/**
 * _setenv - Initialize or modify environment variable
 * @name: Name of environment variable
 * @value: Value to set
 * @envp: Environment array
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, char **envp)
{
	int i = 0;
	size_t namelen;
	char *new_var;
	int env_size;

	if (!name || !value || !envp)
		return (-1);

	namelen = strlen(name);

	while (envp[i])
	{
		if (strncmp(envp[i], name, namelen) == 0 && envp[i][namelen] == '=')
		{

			new_var = malloc(namelen + strlen(value) + 2);
			if (!new_var)
				return (-1);
			sprintf(new_var, "%s=%s", name, value);
			free(envp[i]);
			envp[i] = new_var;
			return (0);
		}
		i++;
	}


	env_size = get_env_size(envp);
	new_var = malloc(namelen + strlen(value) + 2);
	if (!new_var)
		return (-1);

	sprintf(new_var, "%s=%s", name, value);
	envp[env_size] = new_var;
	envp[env_size + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Delete an environment variable
 * @name: Name of variable to delete
 * @envp: Environment array
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name, char **envp)
{
	int i = 0;
	size_t namelen;

	if (!name || !envp)
		return (-1);

	namelen = strlen(name);

	while (envp[i])
	{
		if (strncmp(envp[i], name, namelen) == 0 && envp[i][namelen] == '=')
		{
			free(envp[i]);

			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return (0);
		}
		i++;
	}

	return (-1);
}
