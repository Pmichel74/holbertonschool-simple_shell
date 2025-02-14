#include "main.h"

/**
 * string_to_int - Converts a string representation to an integer
 * @str: Input string to be converted
 * @result: Pointer to store the converted integer
 *
 * Description: Safely converts a string to an integer with robust error handling
 * - Supports positive and negative numbers
 * - Validates each character is a valid digit
 * - Prevents integer overflow
 *
 * Return: 0 on successful conversion, -1 on conversion failure
 */

int string_to_int(const char *str, int *result)
{
    int num = 0;
    int sign = 1;
    const char *ptr = str;

    while (*ptr == ' ' || *ptr == '\t')
        ptr++;

    if (*ptr == '\0')
        return (-1);

    if (*ptr == '-' || *ptr == '+')
    {
        sign = (*ptr == '-') ? -1 : 1;
        ptr++;
    }

    if (*ptr == '\0')
        return (-1);

    while (*ptr)
    {
        if (*ptr < '0' || *ptr > '9')
            return (-1);

        if (num > 214748364 || (num == 214748364 && (*ptr - '0') > 7))
            return (-1);

        num = num * 10 + (*ptr - '0');
        ptr++;
    }

    *result = num * sign;
    return (0);
}
