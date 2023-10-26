#include "main.h"
#include <stdio.h>
/**
* _strchr - Locate character in a string
* @s: Pointer to the string to search
* @c: Character to locate
*
* This function searches for the first occurrence of the character 'c' in the
* string 's'. If the character is found, it returns a pointer to that location
* in the string; otherwise, it returns NULL.
*
* Return: A pointer to the first occurrence of the character 'c' in 's', or
* NULL if the character is not found.
*/
char *_strchr(char *s, char c)
{
while (*s != '\0')
{
if (*s == c)
{
return (s);
}
s++;
}
return (NULL);
}
