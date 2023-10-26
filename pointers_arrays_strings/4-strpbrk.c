#include "main.c"
/**
* _strpbrk - Search a string for any of a set of bytes
* @s: The string to search
* @accept: The string containing bytes to search for
*
* This function searches the string 's' for the first occurrence of any of
* the bytes in the 'accept' string. It returns a pointer to the byte in 's'
* that matches one of the bytes in 'accept', or NULL if no such byte is found.
*
* Return: A pointer to the matching byte in 's' or NULL if no match is found.
*/
char *_strpbrk(char *s, char *accept)
{
while (*s != '\0')
{
char *a = accept;
while (*a != '\0')
{
if (*s == *a)
{
return (s);
}
a++;
}
s++;
}
return (NULL);
}
