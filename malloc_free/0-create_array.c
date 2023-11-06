#include "main.h"
#include <stdlib.h>

/**
* create_array - Create an array of characters and
* initialize itwith a specific character
* @size: The size of the array
* @c: The character to initialize the array with
* Return: Pointer to the created array, or NULL on failure
*/
char *create_array(unsigned int size, char c)
{
char *array;
unsigned int i;
if (size == 0)
{
return (NULL);
}
array = (char *)malloc(size * sizeof(char));
if (array == NULL)
{
return (NULL);
}
for (i = 0; i < size; i++)
{
array[i] = c;
}
return (array);
}
