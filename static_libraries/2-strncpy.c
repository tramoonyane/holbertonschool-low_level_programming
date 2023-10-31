/**
* _strncpy - Copies a string, using at most n bytes from src.
* @dest: The destination string.
* @src: The source string to be copied.
* @n: The maximum number of bytes to copy from src.
*
* Return: A pointer to the resulting copied string (dest).
*/
char *_strncpy(char *dest, char *src, int n)
{
int i;
for (i = 0; i < n && src[i] != '\0'; i++)
{
dest[i] = src[i];
}
while (i < n)
{
dest[i] = '\0';
i++;
}
return (dest);
}
