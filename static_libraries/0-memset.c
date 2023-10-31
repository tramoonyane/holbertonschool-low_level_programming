#include "main.h"
/**
* _memset - Fill memory with a constant byte
* @s: Pointer to the memory area to be filled
* @b: The constant byte to fill the memory with
* @n: The number of bytes to fill
*
* Description: This function fills the first n bytes of the memory area
* pointed to by s with the constant byte b.
*
* Return: A pointer to the memory area s.
*/
char *_memset(char *s, char b, unsigned int n)
{
char *ptr = s;
while (n > 0)
{
*ptr = b;
ptr++;
n--;
}
return (s);
}
