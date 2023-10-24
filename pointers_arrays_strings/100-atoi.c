#include "main.h"
/**
* _atoi - Converts a string to an integer.
* @s: The input string to convert.
*
* Return: The integer value of the string.
*/
int _atoi(char *s)
{
int index = 0;
int negative = 0;
int result = 0;
int foundDigit = 0;
int length = 0;
while (s[length] != '\0')
length++;
while (index < length && foundDigit == 0)
{
if (s[index] == '-')
negative++;
if (s[index] >= '0' && s[index] <= '9')
{
int digit = s[index] - '0';
if (negative % 2)
digit = -digit;
result = result * 10 + digit;
foundDigit = 1;

if (s[index + 1] < '0' || s[index + 1] > '9')
break;
foundDigit = 0;
}
index++;
}

if (foundDigit == 0)
return (0);
return (result);
}
