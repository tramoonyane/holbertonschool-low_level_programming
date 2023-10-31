/**
* _strlen - Returns the length of a string.
*
* @s: A pointer to a null-terminated string.
*
* Description:
* This function calculates and returns the length of a string by
* counting the number of characters in the string until it reaches
* the null terminator ('\0').
*
* Return: The length of the string as an integer.
*/
int _strlen(char *s)
{
int longi = 0;
while (*s != '\0')
{
longi++;
s++;
}
return (longi);
}
