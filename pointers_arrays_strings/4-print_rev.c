#include "main.h"
/**
* print_rev - Prints a string in reverse followed by a new line.
*
* @s: The string to be printed in reverse.
*
* Description:
* This function takes a string and prints its characters in reverse order,
* followed by a newline character ('\n') to create a new line.
*
* Return: No return value.
*/
void print_rev(char *s)
{
int length = 0;

if (s != NULL)
{
while (*s != '\0')
{
length++;
s++;
}
s--;
while (length > 0)
{
_putchar(*s);
s--;
length--;
}
_putchar('\n');
}
}
