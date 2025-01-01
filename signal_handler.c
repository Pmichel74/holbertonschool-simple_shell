#include "main.h"

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number (unused)
 */
void sigint_handler(int sig __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
