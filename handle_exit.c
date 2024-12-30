#include "main.h"

/**
 * handle_exit - Quitte le shell avec le code de statut donné.
 * @args: array of strings containing the command and its arguments.
 *
 * Return: always return 0 for successful execution
 */
int handle_exit(char **args __attribute__((unused)))
{
    exit(0);
}
