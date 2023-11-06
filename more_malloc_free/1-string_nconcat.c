#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* string_nconcat - Concatenate two strings,
* taking the first 'n' characters from s2.
* @s1: The first string.
* @s2: The second string.
* @n: The number of characters to concatenate from s2.
* Return: A pointer to the concatenated string.
*/
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
char *result;
unsigned int len1, len2, total_len;
if (s1 == NULL)
s1 = "";
if (s2 == NULL)
s2 = "";
len1 = strlen(s1);
len2 = strlen(s2);
if (n >= len2)
n = len2;
total_len = len1 + n;
result = malloc(total_len + 1);
if (result == NULL)
return (NULL);
strncpy(result, s1, len1);
strncpy(result + len1, s2, n);
result[total_len] = '\0';
return (result);
}
