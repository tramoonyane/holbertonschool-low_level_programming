#include "main.h"
#include <stdlib.h>

/**
 * strtow - Splits a string into words.
 * @str: The input string to split.
 * Return: A pointer to an array of strings (words), or NULL on failure.
 */
/**
 * strtow - Splits a string into words.
 * @str: The input string to split.
 * Return: A pointer to an array of strings (words), or NULL on failure.
 */
char **strtow(char *str)
{
int num_words, word_index;
char **word_array;
char *word;
if (!str || !*str)
return (NULL);
num_words = count_words(str);
if (num_words == 0)
{
word_array = malloc(sizeof(char *));
if (!word_array)
return (NULL);
word_array[0] = NULL;
return (word_array);
}
word_array = malloc((num_words + 1) * sizeof(char *));
if (!word_array)
return (NULL);
for (word_index = 0; *str; word_index++)
{
while (*str == ' ')
str++;
word = copy_word(str);
if (!word)
{
while (word_index-- > 0)
free(word_array[word_index]);
free(word_array);
return (NULL);
}
word_array[word_index] = word;
while (*str && *str != ' ')
str++;
}
word_array[word_index] = NULL;
return (word_array);
}
/**
 * count_words - Counts the number of words in a string.
 * @str: The input string.
 *
 * Return: The number of words in the string.
 */
int count_words(char *str)
{
int count = 0;
int in_word = 0;
while (*str)
{
if (*str == ' ')
{
in_word = 0;
}
else if (!in_word)
{
count++;
in_word = 1;
}
str++;
}
return (count);
}

/**
 * copy_word - Copies a word from the input string.
 * @str: The input string.
 *
 * Return: A dynamically allocated copy of the word.
 */
char *copy_word(char *str)
{
int len = 0;
int i;
char *word;
while (str[len] && str[len] != ' ')
{
len++;
}
word = (char *)malloc(len + 1);
if (word == NULL)
{
return (NULL);
}
for (i = 0; i < len; i++)
{
word[i] = str[i];
}
word[len] = '\0';
return (word);
}
