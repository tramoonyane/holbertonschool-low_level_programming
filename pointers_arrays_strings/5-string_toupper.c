#include "main.h"
/**
* string_toupper - Changes all lowercase letters in a string to uppercase.
* @str: Pointer to the input string.
*
* Return: Pointer to the modified string.
*
* Description: This function takes a string as input and changes all lowercase
* letters in the string to their uppercase equivalents. The modified string is
* returned as the result.
*/
char *string_toupper(char *str)
{
int i = 0;
while (str[i] != '\0')
{
if (str[i] >= 'a' && str[i] <= 'z')
{
str[i] = str[i] - 32;
}
i++;
}
return str;
}
