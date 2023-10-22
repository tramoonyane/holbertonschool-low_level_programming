#include "main.h"

/**
 * print_most_numbers - Prints numbers except for 2 and 4
 *
 * Description: This function prints all single-digit numbers from 0 to 9,
 * except for 2 and 4, followed by a newline character.
 *
 * Return: void (no return value)
 */

void print_most_numbers(void)
{
char c;
for (c = '0'; c <= '9'; c++)
{
if (!(c == '2' || c == '4'))
_putchar(c);
}
_putchar('\n');
}
