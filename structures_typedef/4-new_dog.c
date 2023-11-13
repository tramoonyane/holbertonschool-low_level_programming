#include <stdio.h>
#include <stdlib.h>
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
dog_t *new_dog;

if (name == NULL || owner == NULL)
return (NULL);
new_dog = malloc(sizeof(dog_t));
if (new_dog == NULL)
exit(EXIT_FAILURE);
new_dog->name = malloc((_strlen(name) + 1) * sizeof(char));
if (new_dog->name == NULL)
{
free(new_dog);
exit(EXIT_FAILURE);
}
_strcpy(new_dog->name, name);
new_dog->age = age;
new_dog->owner = malloc((_strlen(owner) + 1) * sizeof(char));
if (new_dog->owner == NULL)
{
free(new_dog->name);
free(new_dog);
exit(EXIT_FAILURE);
}
_strcpy(new_dog->owner, owner);
return (new_dog);
}
