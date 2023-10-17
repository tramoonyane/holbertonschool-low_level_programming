#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints all possible combinations of single-digit numbers
 * separated by ', ' in ascending order using putchar
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int digit;

    for (digit = 0; digit <= 9; digit++)
    {
        putchar(digit + '0'); // Convert digit to character and print

        if (digit < 9)
        {
            putchar(','); // Print comma
            putchar(' '); // Print space
        }
    }

    putchar('\n'); // Print a newline character

    return (0);
}
