#include "main.h"
/**
* print_chessboard - Print a chessboard
* @a: The 2D array representing the chessboard
*
* This function prints a chessboard represented by a 2D array of characters.
*
* Return: void (no return value)
*/
void print_chessboard(char (*a)[8])
{
int row, col;
for (row = 0; row < 8; row++)
{
for (col = 0; col < 8; col++)
{
_putchar(a[row][col]);
}
_putchar('\n');
}
}
