#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/* more headers goes there */

/* betty style doc for function main goes there */
/**
 * main - A program checking a random number.
 * Return: Always returns 0 to indicate successful execution.
 */
int main(void)
{
	int n;
	/**
 * main - A program checking a random number.
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
