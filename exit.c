#include "main.h"

/**
 *exit_shell - will exit the shell when the word exit is entered by the user
 *@buffer: takes the arg from the user
 *Return: void
 */
void exit_shell(char *buffer)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
}
