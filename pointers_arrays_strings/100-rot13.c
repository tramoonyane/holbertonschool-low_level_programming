#include "main.h"

/**
* rot13 - Encodes a string using the ROT13 cipher.
* @str: The input string to be encoded.
*
* Return: A pointer to the encoded string.
*/
char *rot13(char *str)
{
int i = 0, j;
char a[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char b[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";

while (str[i])
{
j = 0;
while (j < 52)
{
if (a[j] == str[i])
{
str[i] = b[j];
break;
}
j++;
}
i++;
}
return (str);
}
