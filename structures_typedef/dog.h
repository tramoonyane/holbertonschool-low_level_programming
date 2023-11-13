#ifndef DOG_H
#define DOG_H
/**
 * struct dog - Represents information about a dog.
 * @name: Pointer to a string representing the name of the dog.
 * @age: The age of the dog as a floating-point number.
 * @owner: Pointer to a string representing the owner of the dog.
 *
 * Description: This struct encapsulates information about a dog,
 * including its name, age, and owner. It is designed to be used
 * for creating variables that represent individual dogs.
 */
struct dog
{
char *name;
float age;
char *owner;
};
void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);

#endif
