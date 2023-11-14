#include <stdlib.h>

int _putchar(char c);

/**
 * print_name - Prints a name using function pointer
 * @name: The name to be printed
 * @f: Pointer to a function that prints a string
 *
 * Description: This function takes a name and a function pointer as arguments
 * and uses the function pointer to print the name.
 */
void print_name(char *name, void (*f)(char *))
{
    if (name != NULL && f != NULL) {
        f(name);
    }
}
