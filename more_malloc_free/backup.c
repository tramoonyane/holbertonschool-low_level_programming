#include "main.h"
#include <stdlib.h>

/**
 * _realloc - Reallocate a memory block using malloc and free.
 * @ptr: Pointer to the memory previously allocated with malloc.
 * @old_size: Size, in bytes, of the allocated space for ptr.
 * @new_size: New size, in bytes, of the new memory block.
 * Return: A pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
  char *new_ptr;
  if (new_size == 0 && ptr)
    {
      free(ptr);
      return (NULL);
    }
  new_ptr = malloc(new_size);
  if (!new_ptr)
    {
      return (NULL);
    }
  if (ptr != NULL)
    {
      unsigned int i;
      char *p = ptr;
      char *np = new_ptr;

      for (i = 0; i < old_size; i++)
	{
	  np[i] = p[i];
	}
      free(ptr);
    }
  return (new_ptr);
}
