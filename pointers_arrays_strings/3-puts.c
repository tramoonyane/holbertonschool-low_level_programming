#include "main.h"

/**
* _puts - Prints a string followed by a new line to stdout.
*
* @str: The string to be printed.
*
* Description:
* This function prints the characters of a string to the standard output
* (stdout) followed by a newline character ('\n') to create a new line.
*
* Return: No return value.
*/

#include "main.h"
void _puts(char *str)
{
while (*str != '\0')
{
_putchar(*str++);
}
_putchar('\n');
}
