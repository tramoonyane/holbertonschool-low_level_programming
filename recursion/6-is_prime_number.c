#include "main.h"

/**
* is_prime_number - Check if a number is prime recursively
* @n: The input number
* Return: 1 if n is prime, 0 if not
*/
int is_prime_number(int n)
{
if (n <= 1)
return (0);
return (is_prime_recursive(n, 2));
}

/**
* is_prime_recursive - Helper function to check if a number is prime recursively
* @n: The input number
* @divisor: The current divisor to check
* Return: 1 if n is prime, 0 if not
*/
int is_prime_recursive(int n, int divisor)
{
if (divisor == n)
return (1);
if (n % divisor == 0)
return (0);
return (is_prime_recursive(n, divisor + 1));
}
