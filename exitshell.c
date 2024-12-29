#include "main.h"

/**
 * is_valid_number - Checks if a string is a valid non-negative integer.
 * @str: The string to check.
 *
 * Return: 1 if the string is a valid non-negative integer, 0 otherwise.
 */
int is_valid_number(const char *str)
{
    int i; /* Déclaration de i avant la boucle*/
    if (str == NULL || *str == '\0')
        return (0);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return (0);
    }

    return (1);
}

/**
 * exitshell - Exits the shell with a given status code.
 * @buffer: The command line buffer, which may contain an exit status.
 *
 * Return:
 * -99 if not the exit command
 * exit status code otherwise
 */
int exitshell(char *buffer)
{
	int status = 0;
	char *arg;

	char *exit_token = strtok(buffer, " ");

	if (strcmp(exit_token, "exit") == 0)
	{
		arg = strtok(NULL, " ");
		if (arg != NULL)
		{
			if (is_valid_number(arg))
			{
				status = atoi(arg);
				return status;
			}
			else
			{
				/* Handle the error for non-numeric argument here */
				fprintf(stderr, "Error: Invalid exit status argument.\n");
				return (2); /* You can choose an appropriate error code */
			}
		}
		else
		{
			return (0); /* No argument provided, exit with 0 */
		}
	}

	return (-99); /* Not an exit command */
}
