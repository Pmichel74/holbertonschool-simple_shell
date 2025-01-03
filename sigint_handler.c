#include "main.h"

/**
 * sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigint_handler(int sig_num)
{
	(void)sig_num;
	write(STDOUT_FILENO, "\n$ ", 3);
}
