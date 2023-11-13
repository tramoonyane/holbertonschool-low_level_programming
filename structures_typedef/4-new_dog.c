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
dog_t *new_dog;
if (name == NULL || owner == NULL)
return (NULL);
new_dog = malloc(sizeof(dog_t));
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
/**
 * free_dog - Frees memory allocated for a dog structure.
 * @d: Pointer to a dog_t structure.
 *
 * Description: This function frees the memory allocated for the
 * name, owner, and the dog structure itself. It should be called
 * when the dog structure is no longer needed to avoid memory leaks.
 */
void free_dog(dog_t *d)
{
if (d == NULL)
return;
free(d->name);
free(d->owner);
free(d);
}
/**
 * main - Entry point of the program.
 *
 * Return: 0 on success, 1 on failure.
 *
 * Description: The main function demonstrates the usage of the new_dog
 * function to create a dog, prints information about the dog, and then
 * frees the allocated memory using the free_dog function.
 */
int main(void)
{
char name[] = "Ghost";
float age = 4.75;
char owner[] = "Jon Snow";

dog_t *my_dog = new_dog(name, age, owner);
if (my_dog == NULL)
{
printf("Error creating dog.\n");
return (1);
}
rintf("My name is %s, I am %.2f, and my owner is %s\n", my_dog->name, my_dog->age, my_dog->owner);
free_dog(my_dog);
return (0);
}
