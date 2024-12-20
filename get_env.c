#include "main.h"

/**
 * get_env - prints the current environment variables.
 * @env: pointer to strings of environment vairiables
 */
void get_env(char **env)
{
	size_t var = 0;

	While(env[var])
	{
		write(STDOUT_FILENO, env[var], strlen(env[var]));
		write(STDOUT_FILENO, "\n", 1);
		var++;
	}
}
