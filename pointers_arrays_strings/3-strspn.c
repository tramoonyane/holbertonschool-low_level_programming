#include "main.h"
/**
* _strspn - Get the length of a prefix substring
* @s: The string to search
* @accept: The string containing characters to search for
*
* This function calculates the length of the prefix substring in 's' that
* consists only of characters from the 'accept' string. It counts the number
* of continuous characters in 's' that match any character in 'accept'.
*
* Return: The number of bytes
* in the initial segment of 's' that match 'accept'.
*/
unsigned int _strspn(char *s, char *accept)
{
unsigned int length = 0;
int found;
while (*s != '\0')
{
found = 0;
for (int i = 0; accept[i] != '\0'; i++)
{
if (*s == accept[i])
{
found = 1;
break;
}
}
if (found)
{
length++;
s++;
}
else
{
break;
}
}
return (length);
}
