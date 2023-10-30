#include "main.h"

/**
* _sqrt_recursion - Calculate the natural square root of a number recursively
* @n: The input number
* Return: The natural square root of n, or -1 for error
*/
int _sqrt_recursion(int n)
{
if (n < 0)
return (-1);
if (n == 0 || n == 1)
return (n);
return (_sqrt_helper(n, 1));
}
