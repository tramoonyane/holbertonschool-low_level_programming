#include <stdio.h>

/**
 * main - Entry point of the program
 *
 * Description: This program prints all lowercase hexadecimal digits (0-9, a-f)
 * followed by a newline character using the putchar function only three times.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char ch;

	for (ch = '0'; ch <= '9'; ch++)
		putchar(ch);

	for (ch = 'a'; ch <= 'f'; ch++)
		putchar(ch);

	putchar('\n');

	return (0);
}
