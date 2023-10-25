#include "main.h"
/**
* _strncat - Concatenates two strings, using at most n bytes from src.
* @dest: The destination string.
* @src: The source string to be appended.
* @n: The maximum number of bytes to use from src.
*
* Return: A pointer to the resulting concatenated string (dest).
*/
char *_strncat(char *dest, const char *src, int n)
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
