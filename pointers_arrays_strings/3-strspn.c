/**
* _strspn - Get the length of a prefix substring
* @s: The string to search
* @accept: The string containing characters to search for
*
* This function calculates the length of the prefix substring in 's' that
* consists only of characters from the 'accept' string. It counts the number
* of continuous characters in 's' that match any character in 'accept'.
*
* Return: The number of bytes in the initial segment of 's' that match 'accept'.
*/
unsigned int _strspn(char *s, char *accept)
{
unsigned int length = 0;
int found;
unsigned int i;
while (*s != '\0')
{
found = 0;
i = 0;
while (accept[i] != '\0')
{
if (*s == accept[i])
{
found = 1;
break;
}
i++;
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
