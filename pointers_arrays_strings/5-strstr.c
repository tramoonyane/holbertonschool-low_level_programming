#include "main.h"
/**
* _strstr - Locate a substring in a string
* @haystack: The string to search in
* @needle: The substring to find
*
* This function finds the first occurrence of the substring 'needle' in the
* string 'haystack'. The terminating null bytes are not compared.
*
* Return: A pointer to the beginning of the located substring, or NULL if
* the substring is not found.
*/
char *_strstr(char *haystack, char *needle)
{
char *h, *n;
if (*needle == '\0')
{
return (haystack);
}
while (*haystack != '\0')
{
h = haystack;
n = needle;
while (*n != '\0' && *h == *n)
{
h++;
n++;
}
if (*n == '\0')
{
return (haystack);
}
haystack++;
}
return (NULL);
}
