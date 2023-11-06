#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* _calloc - Allocate memory for an array and initialize it to zero.
* @nmemb: Number of elements in the array.
* @size: Size of each element in bytes.
* Return: A pointer to the allocated memory, or NULL on failure.
*/
void *_calloc(unsigned int nmemb, unsigned int size)
{
void *ptr;
if (nmemb == 0 || size == 0)
return (NULL);
ptr = malloc(nmemb * size);
if (ptr == NULL)
return (NULL);
memset(ptr, 0, nmemb * size);
return (ptr);
}
