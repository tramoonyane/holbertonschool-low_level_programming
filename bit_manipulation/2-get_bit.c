#include "main.h"

/**
 * get_bit - returns the value of a bit at a given index
 * @n: unsigned long int number
 * @index: index of the bit to get
 *
 * Return: value of the bit at index or -1 if an error occurred
 */
int get_bit(unsigned long int n, unsigned int index)
{
if (index >= sizeof(unsigned long int) * 8)
{
return (-1);
}
unsigned long int mask = 1UL << index;
return (((n & mask) != 0) ? 1 : 0);
}
