#include "main.h"
/**
* _strcat - Concatenates two strings.
* @dest: The destination string.
* @src: The source string to be appended.
*
* Return: A pointer to the resulting concatenated string (dest).
*/
char *_strcat(char *dest, char *src)
{
char *dest_ptr = dest;
while (*dest_ptr != '\0')
{
dest_ptr++;
}
while (*src != '\0')
{
*dest_ptr = *src;
dest_ptr++;
src++;
}
*dest_ptr = '\0';
return (dest);
}
