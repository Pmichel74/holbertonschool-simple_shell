#include "main.h"

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C)
 * @sig: Signal number (unused)
 */
void sigint_handler(int sig __attribute__((unused)))
{
	signal(SIGINT, sigint_handler);
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}
