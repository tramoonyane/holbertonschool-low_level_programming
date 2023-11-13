#include <stdlib.h>
#include "dog.h"
/**
 * init_dog - Initializes a variable of type struct dog.
 * @d: Pointer to a struct dog.
 * @name: Pointer to a string representing the name of the dog.
 * @age: The age of the dog as a floating-point number.
 * @owner: Pointer to a string representing the owner of the dog.
 *
 * Return: void.
 */
void init_dog(struct dog *d, char *name, float age, char *owner)
{
if (d == 0)
return;

d->name = name;
d->age = age;
d->owner = owner;
}
