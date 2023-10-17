#include <unistd.h>

/**
 * main - Entry point
 *
 * Description: Prints single digit numbers from 0 to 9 on a single line,
 *              followed by a newline character.
 * Return: 0 (Success)
 */
int main(void)
{
    int digit;

    digit = '0';
    while (digit <= '9')
    {
        putchar(digit);
        digit++;
    }
    putchar('\n');

    return (0);
}
