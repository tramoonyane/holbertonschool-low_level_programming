#include <stdio.h>
/**
 * main - Entry point of the program
 *
 * This function prints all single-digit numbers of base 10
 * starting from 0, each followed by a new line.
 *
 * Return: 0 (Success)
 */
int main(void)
{
    int number = 0;

    while (number < 10)
    {
        printf("%d\n", number);
        number++;
    }

    return (0);
}
