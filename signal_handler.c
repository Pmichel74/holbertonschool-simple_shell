#include "main.h"

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number
 */
void sigint_handler(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n$ ", 3);
}

