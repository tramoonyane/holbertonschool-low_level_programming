/* helper_file2.c */

#include "Shell.h"

/**
 * print_environment - Prints the current environment variables.
 */
void print_environment() {
    extern char **environ;
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
}


