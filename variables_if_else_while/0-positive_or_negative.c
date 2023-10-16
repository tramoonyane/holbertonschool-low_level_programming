#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/* more headers goes there */

/* betty style doc for function main goes there */
/**
 * main - Entry point of the program that checks a random number's sign.
 *
 * This program generates a random number and checks whether it is positive,
 * negative, or zero. It uses the srand and rand functions from the <stdlib.h>
 * library to generate the random number, and the time function from <time.h>
 * to seed the random number generator. The result is then compared, and a
 * message indicating the sign of the number is printed to the standard output.
 *
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
