#include <string.h>
#include <stdlib.h>

/* Custom implementation of getenv function */
/* This function searches for an environment variable by name */
/* and returns its value if found, or NULL if not found */

extern char **environ;

char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);
	char *value;


	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			value = &environ[i][len + 1];
			return (value);
		}
		i++;
	}

	return (NULL);
}
#include <stdio.h>

/* Main function to demonstrate the usage of _getenv */
int main(void)
{
	char *value = _getenv("PATH");

	if (value)
	{
		printf("PATH = %s\n", value);
	}
	else
	{
		printf("PATH not found\n");
	}

}
