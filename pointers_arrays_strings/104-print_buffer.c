#include "main.h"
#include <stdio.h>

/**
* print_buffer - Prints the content of a buffer with a specific format.
* @b: The buffer to be printed.
* @size: The number of bytes to be printed from the buffer.
*
* Description:
* - The function prints the content of a buffer in a specific format.
* - Each line starts with the position of the first byte of the line in hexadecimal.
* - Each line shows the hexadecimal content of the buffer, 2 bytes at a time, separated by a space.
* - If the byte is a printable character, it prints the character, otherwise, it prints a dot ('.').
* - Each line ends with a newline character ('\n').
* - If size is 0 or less, the output consists of a newline character only.
*
* Return: No return value.
*/

void print_buffer(char *b, int size)
{
if (size <= 0) {
printf("\n");
return;
}
  
int i, j;

for (i = 0; i < size; i += 10)
{
printf("%08x: ", i);

for (j = i; j < i + 10; j++)
{
if (j < size)
{
printf("%02x", b[j]);
if (j % 2 != 0)
printf(" ");
}
else
{
printf("  ");
}
}

printf(" ");
for (j = i; j < i + 10; j++)
{
if (j < size)
{
if (b[j] >= 32 && b[j] <= 126)
printf("%c", b[j]);
else
printf(".");
}
else
{
printf(" ");
}
}

printf("\n");
}
}

int main()
{
char buffer[] = "This is a string!\nAnd this is the rest of the #buffer :)";
int size = sizeof(buffer) - 1;
print_buffer(buffer, size);

  return (0);
}
