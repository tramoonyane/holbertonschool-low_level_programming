#include "main.h"

/**
 * print_binary - prints the binary representation of a number
 * @n: unsigned long int number to print in binary
 */
void print_binary(unsigned long int n)
{
unsigned long int mask = 1UL << (sizeof(unsigned long int) * 8 - 1);
int flag = 0;
if (n == 0)
{
_putchar('0');
return;
}
while (mask)
{
if ((n & mask) || flag)
{
flag = 1;
_putchar((n & mask) ? '1' : '0');
}
mask >>= 1;
}
}
