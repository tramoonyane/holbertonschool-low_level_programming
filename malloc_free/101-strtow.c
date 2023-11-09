#include "main.h"
#include <stdlib.h>

/**
 * free_word_array - Frees the memory allocated for word_array.
 * @word_array: The word array to free.
 */
void free_word_array(char **word_array)
{
int i;
if (word_array)
{
for (i = 0; word_array[i] != NULL; i++)
{
free(word_array[i]);
}
free(word_array);
}
}
/**
 * strtow - Splits a string into words.
 * @str: The input string to split.
 * Return: A pointer to an array of strings (words), or NULL on failure.
 */
char **strtow(char *str)
{
int num_words, len, i, word_index = 0;
char **word_array;
char *word;
char *end;
if (!str || !*str)
return (NULL);
num_words = count_words(str);
word_array = malloc((num_words + 1) * sizeof(char *));
if (!word_array)
return (NULL);
while (*str)
{
while (*str == ' ')
str++;
if (*str == '\0')
break;
end = str;
while (*end && *end != ' ')
end++;
len = end - str;
word = malloc(len + 1);
if (!word)
{
free_word_array(word_array);
return (NULL);
}
for (i = 0; i < len; i++)
{
word[i] = str[i];
}
word[len] = '\0';
word_array[word_index++] = word;
str = end;
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
