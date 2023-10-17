#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Print the lowercase alphabet in reverse on a single line
 * without spaces using putchar function.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char letter = 'z';
while (letter >= 'a')
{
putchar(letter);
letter--;
}
putchar('\n');
return (0);
}
