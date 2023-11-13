#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dog.h"

/**
 * new_dog - Creates a new dog.
 * @name: Pointer to a string representing the name of the dog.
 * @age: The age of the dog as a floating-point number.
 * @owner: Pointer to a string representing the owner of the dog.
 *
 * Return: A pointer to the newly created dog_t structure.
 *         NULL if memory allocation fails or if any input is NULL.
 */
dog_t *new_dog(char *name, float age, char *owner)
{
if (name == NULL || owner == NULL)
return (NULL);
dog_t *new_dog = malloc(sizeof(dog_t));
if (new_dog == NULL)
return (NULL);
new_dog->name = strdup(name);
if (new_dog->name == NULL)
{
free(new_dog);
return (NULL);
}
new_dog->age = age;
new_dog->owner = strdup(owner);
if (new_dog->owner == NULL)
{
free(new_dog->name);
free(new_dog);
return (NULL);
}
return (new_dog);
}
