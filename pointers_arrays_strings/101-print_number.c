#include "main.h"

/**
* print_number - Prints an integer to the standard output.
* @n: The integer to be printed.
*
* Description:
* - The function prints an integer to the standard output.
* - If the integer is negative, it first prints a '-' sign.
* - It handles the integer as an unsigned integer to avoid issues with INT_MIN.
* - The integer is printed digit by digit, starting from the leftmost digit.
*
* Return: No return value.
*/
void print_number(int n)
{
unsigned int x;
if (n < 0)
{
_putchar('-');
n *= -1;
}

x = n;

if (x / 10)
print_number(x / 10);
_putchar(x % 10 + '0');
}
