#include "main.h"

#define BUF_FLUSH -1

/**
 * _puts - prints a string
 * @str: pointer to the string
 *
 * Return: number of chars written
 */
static int _puts(const char *str)
{
	return (write(STDOUT_FILENO, str, strlen(str)));
}

/**
 * sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_handler(int sig_num)
{
	(void)sig_num;
	_puts("\n$ ");
	fflush(stdout);
}
