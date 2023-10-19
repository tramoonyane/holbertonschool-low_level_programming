#include "main.h"

/**
 * _abs - Computes the absolute value of an integer.
 * @c: The integer for which the absolute value is computed.
 *
 * Return: The absolute value of 'c' or zero if 'c' is non-negative.
 */

int _abs(int c)
{
if (c < 0)
{
int abs_val;
abs_val = c * -1;
return (abs_val);
}
return (c);
}
