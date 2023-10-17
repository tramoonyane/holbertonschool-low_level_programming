#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * This program prints all single-digit numbers of base 10
 * starting from 0 in a single line, followed by a new line.
 *
 * Return: 0 (Success)
 */
int main(void)
{
int i;
for (i = 0; i <= 9; i++)
{
printf("%d", i);
if (i < 9)
printf("");
else
printf("\n");
}
return (0);
}
