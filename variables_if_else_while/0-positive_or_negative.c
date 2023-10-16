#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/* more headers goes there */

/* betty style doc for function main goes there */
int main(void)
{
	int n;
	/**
 * main - Entry point for a program that determines whether a random number is positive, negative, or zero.
 * This program generates a random number and checks if it is positive, negative, or zero. It then prints a message
 * indicating the result.
 * Return: Always returns 0 to indicate successful execution.
 */
	srand(time(0));
	n = rand() - RAND_MAX / 2;
	/* your code goes there */
	if (n > 0)
	printf("%d is positive\n", n);
	else if (n < 0)
	printf("%d is positive\n", n);
	else
	printf("%d is zero\n", n);
	return (0);
}
