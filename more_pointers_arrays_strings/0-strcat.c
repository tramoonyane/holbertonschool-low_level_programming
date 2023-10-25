/**
* _strcat - Concatenates two strings.
* @dest: The destination string to which src will be appended.
* @src: The source string that will be appended to dest.
*
* Return: A pointer to the resulting string (dest).
*/
char *_strcat(char *dest, char *src)
{
char *originalDest = dest;
while (*dest != '\0')
{
dest++;
}
while (*src != '\0')
{
*dest = *src;
dest++;
src++;
}
*dest = '\0';
return originalDest;
}
