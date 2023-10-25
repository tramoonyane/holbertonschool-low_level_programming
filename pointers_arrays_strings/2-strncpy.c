#include "main.h"
/**
* _strncpy - Copies at most n bytes
* from the source string to the destination string.
* @dest: The destination string.
* @src: The source string to be copied from.
* @n: The maximum number of bytes to copy from src.
*
* Return: A pointer to the resulting copied string (dest).
*/
char *_strncpy(char *dest, char *src, int n)
{
char *dest_ptr = dest;
for (; *dest_ptr != '\0'; dest_ptr++)
{

}
for (; *src != '\0' && n > 0; n--)
{
*dest_ptr = *src;
dest_ptr++;
src++;
}
*dest_ptr = '\0';
return (dest);
}
