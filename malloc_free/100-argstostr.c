#include "main.h"
#include <stdlib.h>

/**
 * _strlen - Calculate the length of a string.
 * @s: The string to calculate the length of.
 * Return: The length of the string.
 */
int _strlen(char *s)
{
int len = 0;
while (s[len])
{
len++;
}
return (len);
}

/**
 * argstostr - Concatenate all the arguments of the program.
 * @ac: The argument count.
 * @av: The array of argument strings.
 * Return: A pointer to a new string, or NULL if it fails.
 */
char *argstostr(int ac, char **av)
{
int total_length = 0;
int i, j, len;
char *concatenated_str;
int current_position; 
if (ac == 0 || av == NULL)
return (NULL);

for (i = 0; i < ac; i++)
{
total_length += _strlen(av[i]) + 1;
}
concatenated_str = (char *)malloc(sizeof(char) * total_length + 1);
if (concatenated_str == NULL)
return (NULL);
current_position = 0;
for (i = 0; i < ac; i++)
{
len = _strlen(av[i]);
for (j = 0; j < len; j++)
{
concatenated_str[current_position] = av[i][j];
current_position++;
}
concatenated_str[current_position] = '\n';
current_position++;
}
concatenated_str[current_position] = '\0';
return (concatenated_str);
}
