/* simple_shell_path.c */

#include "Shell.h"

/**
 * parse_path - Tokenizes the PATH environment variable into directories.
 *
 * Return: Returns an array of directories.
 */
char **parse_path(void)
{
    char *path = get_path();
    char *path_copy = strdup(path);
    char **directories = allocate_directories(1);

    char *token = strtok(path_copy, ":");
    int count = 0;

    while (token != NULL)
    {
        add_directory(&directories, token, count++);
        token = strtok(NULL, ":");
    }

    directories = realloc(directories, (count + 1) * sizeof(char *));
    if (directories == NULL)
    {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    directories[count] = NULL;

    free(path_copy);
    return directories;
}

/**
 * add_directory - Adds a directory to the directories array.
 *
 * @directories: Pointer to the array of directories.
 * @token: The directory string to be added.
 * @count: Index of the directory being added.
 */
void add_directory(char ***directories, char *token, int count)
{
    *directories = realloc(*directories, (count + 1) * sizeof(char *));
    if (*directories == NULL)
    {
        perror("realloc error");
        exit(EXIT_FAILURE);
    }
    (*directories)[count] = token;
}

/**
 * allocate_directories - Allocates memory for the directories array.
 *
 * @size: Size of the array to be allocated.
 * Return: Pointer to the newly allocated array of directories.
 */
char **allocate_directories(int size)
{
    char **directories = malloc(size * sizeof(char *));
    if (directories == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    return directories;
}

/**
 * get_path - Retrieves the PATH environment variable.
 *
 * Return: Pointer to the PATH environment variable string.
 */
char *get_path(void)
{
    char *path = getenv("PATH");

    if (path == NULL || *path == '\0')
    {
        fprintf(stderr, "No PATH variable found or empty.\n");
        exit(EXIT_FAILURE);
    }
    return path;
}
