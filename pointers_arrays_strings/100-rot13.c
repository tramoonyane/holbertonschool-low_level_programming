#include "main.h"
/**
* rot13 - Encodes a string using the ROT13 cipher.
* @str: The input string to be encoded.
*
* Return: A pointer to the encoded string.
*/
char *rot13(char *str)
{
if (str == NULL)
return (NULL);
char *ptr = str;
while (*ptr)
{
char c = *ptr;
if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
{
char base = (c >= 'A' && c <= 'Z') ? 'A' : 'a';
*ptr = (c - base + 13) % 26 + base;
}
ptr++;
}
return (str);
}
