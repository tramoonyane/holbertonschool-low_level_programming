#include "main.h"
#include <stdlib.h>

/**
 * _realloc - Reallocate a memory block using malloc and free.
 * @ptr: Pointer to the memory previously allocated with malloc.
 * @old_size: Size, in bytes, of the allocated space for ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: A pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *new_ptr;
if (new_size == 0)
{
free(ptr);
return (NULL);
}
if (ptr == NULL)
{
return (malloc(new_size));
}
if (new_size == old_size)
{
return (ptr);
}
if (new_size > old_size)
{
new_ptr = malloc(new_size);
if (new_ptr == NULL)
{
return (NULL);
}
for (unsigned int i = 0; i < old_size; i++)
{
((char *)new_ptr)[i] = ((char *)ptr)[i];
}
}
else
{
new_ptr = malloc(new_size);
if (new_ptr == NULL)
{
return (NULL);
}
for (unsigned int i = 0; i < new_size; i++)
{
((char *)new_ptr)[i] = ((char *)ptr)[i];
}
}
free(ptr);
return (new_ptr);
}
