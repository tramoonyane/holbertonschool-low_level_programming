#include "main.h"
#include <stdlib.h>

/**
* _strdup - Duplicate a string.
* @str: The string to duplicate.
* Return: Pointer to the duplicated string, or NULL on failure.
*/
char *_strdup(char *str)
{
char *duplicate;
int length = 0;
int i;
if (str == NULL)
return (NULL);
while (str[length] != '\0')
length++;
duplicate = (char *)malloc((length + 1) * sizeof(char));
if (duplicate == NULL)
return (NULL);
for (i = 0; i <= length; i++)
duplicate[i] = str[i];
return (duplicate);
}
