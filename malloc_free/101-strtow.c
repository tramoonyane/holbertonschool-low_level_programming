#include "main.h"
#include <stdlib.h>

/**
 * strtow - Splits a string into words.
 * @str: The input string to split.
 * Return: A pointer to an array of strings (words), or NULL on failure.
 */
char **strtow(char *str)
{
int num_words, word_index;
char **word_array;
if (str == NULL || str[0] == '\0')
return (NULL);
num_words = count_words(str);
word_array = (char **)malloc((num_words + 1) * sizeof(char *));
if (word_array == NULL)
return (NULL);
word_index = 0;
while (*str)
{
if (*str == ' ')
{
str++;
}
else
{
char *word = copy_word(str);
if (word == NULL)
{
for (int i = 0; i < word_index; i++)
{
free(word_array[i]);
}
free(word_array);
return (NULL);
}
word_array[word_index] = word;
word_index++;
while (*str && *str != ' ')
{
str++;
}
}
}
word_array[word_index] = NULL;
return (word_array);
}
