#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - Generate random valid passwords for 101-crackme.
 *
 * Description:
 * This program generates random valid passwords for the 101-crackme program.
 * It creates a sequence of characters within the ASCII range 48-125
 * that sums up to 2772, which is a valid password for the crackme program.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int password[100];
    int i, total;

    total = 0;
    srand(time(NULL));

    i = 0;
    while (total < 2772 && i < 100) {
        password[i] = rand() % 78 + 48; // Generate random characters within the ASCII range
        total += password[i];
        putchar(password[i]);
        i++;
    }

    if (total > 2772) {
        password[i - 1] -= (total - 2772); // Adjust the last character to reach the target
        putchar(password[i - 1]);
    }

    return (0);
}
