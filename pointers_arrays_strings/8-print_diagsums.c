#include "main.h"
#include <stdio.h>

/**
* print_diagsums - Prints the sum of the two diagonals of a square matrix.
* @a: The square matrix of integers.
* @size: The size of the matrix (number of rows or columns).
*
* Description:
* This function calculates and prints
* the sum of the main diagonal (from top-left to
* bottom-right) and the sum of
* the secondary diagonal (from top-right to bottom-left)
* of a square matrix of integers.
*/
void print_diagsums(int *a, int size)
{
int main_diag_sum = 0;
int secondary_diag_sum = 0;
int i;
for (i = 0; i < size; i++)
{
main_diag_sum += a[i];
a += size;
}
a -= size;
for (i = 0; i < size; i++)
{
secondary_diag_sum += a[i];
a -= size;
}
printf("%d, %d\n", main_diag_sum, secondary_diag_sum);
}
