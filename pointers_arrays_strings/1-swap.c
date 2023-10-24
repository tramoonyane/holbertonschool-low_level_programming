#include "main.h"

/**
* swap_int - Swaps the values of two integers.
*
* @a: Pointer to the first integer.
* @b: Pointer to the second integer.
*
* Description:
* This function takes two pointers to integers and swaps their values.
*
* Return: No return value.
*/
void swap_int(int *a, int *b)
{
int temp;

if (a != NULL && b != NULL)
{
temp = *a;
*a = *b;
*b = temp;
}
}
