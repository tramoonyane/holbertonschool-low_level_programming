#include "main.h"
#include <stdlib.h>

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
while (*str == '')
str++;
if (*str == '\0')
break;
end = str;
while (*end && *end != '')
end++;
len = end - str;
word = malloc(len + 1);
if (!word)
{
while (word_index-- > 0)
free(word_array[word_index]);
free(word_array);
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
if (*str == '')
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
