#include "main.h"

/**
* factorial - Calculate the factorial of a number recursively
* @n: The input number
* Return: The factorial of n, or -1 for error
*/
int factorial(int n)
{
if (n < 0)
return (-1);
if (n == 0 || n == 1)
return (1);
return (n * factorial(n - 1));
}
