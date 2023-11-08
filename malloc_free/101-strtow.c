#include "main.h"
#include <stdlib.h>

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
while (str[len] && str[len] != ' ')
{
len++;
}
char *word = (char *)malloc(len + 1);
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

/**
 * strtow - Splits a string into words.
 * @str: The input string to split.
 * Return: A pointer to an array of strings (words), or NULL on failure.
 */
char **strtow(char *str)
{
int num_words, word_index,
char **word_array;
if (str == NULL || str[0] == '\0')
{
return (NULL);
}
num_words = count_words(str);
word_array = (char **)malloc((num_words + 1) * sizeof(char *));
if (word_array == NULL)
{
return (NULL);
}
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
for (i = 0; i < word_index; i++)
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
