#include "shell.h"
/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive();
	else
		shell_no_interactive();

	return (0);
}
