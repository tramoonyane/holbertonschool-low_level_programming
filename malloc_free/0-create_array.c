#include "main.h"
#include <stdlib.h>

/**
* create_array - Create an array of characters and initialize it with a specific character
* @size: The size of the array
* @c: The character to initialize the array with
* Return: Pointer to the created array, or NULL on failure
*/
char *create_array(unsigned int size, char c)
{
if (size == 0)
{
return (NULL);
}
char *array = (char *)malloc(size * sizeof(char));
if (array == NULL)
{
return (NULL);
}
unsigned int i;
for (i = 0; i < size; i++)
{
array[i] = c;
}
return array;
}
int main()
{
unsigned int size = 10;
char fill_char = 'A';
char *result = create_array(size, fill_char);
if (result != NULL)
{
for (unsigned int i = 0; i < size; i++)
{
_putchar(result[i]);
}
free(result);
}
return (0);
}
