#include "main.h"

/**
* _strlen - Calculate the length of a string
* @s: The input string
* Return: The length of the string
*/
int _strlen(char *s)
{
if (*s == '\0')
return (0);
return (1 + _strlen(s + 1));
}

/**
* _print_rev_recursion - Print a string in reverse recursively
* @s: The string to be printed in reverse
*/
void _print_rev_recursion(char *s)
{
int len = _strlen(s);
if (len > 0)
{
_putchar(s[len - 1]);
_print_rev_recursion(s);
}
}
