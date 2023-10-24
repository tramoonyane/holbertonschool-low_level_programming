#include "main.h"
/**
* _strcpy - a function that copies the string pointed to by src
* @dest: copy to
* @src: copy from
* Return: string
*/
char *_strcpy(char *dest, char *src)
{
int l = 0;
int x = 0;
while (src[l] != '\0')
{
l++;
}
while (x < l)
{
dest[x] = src[x];
x++;
}
dest[l] = '\0';
return (dest);
}
