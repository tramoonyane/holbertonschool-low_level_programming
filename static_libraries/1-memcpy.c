#include "main.h"
/**
* _memcpy - Copy memory area
* @dest: Destination memory area
* @src: Source memory area
* @n: Number of bytes to copy
*
* This function copies 'n' bytes from the source memory area 'src' to the
* destination memory area 'dest'. It does not check for buffer overflow,
* so make sure 'dest' has enough space for 'n' bytes.
*
* Return: A pointer to the destination memory area 'dest'.
*/
char *_memcpy(char *dest, char *src, unsigned int n)
{
char *original_dest = dest;
while (n > 0)
{
*dest = *src;
dest++;
src++;
n--;
}
return (original_dest);
}
