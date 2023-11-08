#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * strtow - Splits a string into words.
 * @str: The string to split.
 * Return: Returns a pointer to an array of strings (words).
 */
char **strtow(char *str)
{
if (str == NULL || str[0] == '\0')
return (NULL);
int word_count = 0;
char **words = NULL;
int i = 0, j = 0, k = 0, word_len = 0;
word_count = word_count(str);
words = (char **)malloc(sizeof(char *) * (word_count + 1));
if (words == NULL)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
{
if (str[i] != ' ')
{
word_len = word_length(str, i);
words[j] = (char *)malloc(sizeof(char) * (word_len + 1));
if (words[j] == NULL)
{
free_words_array(words, j);
return (NULL);
}
for (k = 0; k < word_len; k++, i++)
words[j][k] = str[i];
words[j][k] = '\0';
j++;
}
}
words[j] = NULL;
return (words);
}
/**
 * word_count - Counts the number of words in a string.
 * @str: The string to count the words in.
 * Return: The number of words in the string.
 */
int word_count(char *str)
{
int count = 0, i = 0;
while (str[i] != '\0')
{
if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
count++;
i++;
}
return (count);
}
/**
 * word_length - Calculates the length of a word starting from the given position.
 * @str: The string to calculate the word length from.
 * @start: The starting position of the word.
 *
 * Return: The length of the word.
 */
int word_length(char *str, int start)
{
int length = 0;
int i = start;
while (str[i] != ' ' && str[i] != '\0')
{
length++;
i++;
}
return (length);
}
/**
 * free_words_array - Frees memory allocated for each word in the words array, and the array itself.
 * @words: The array of words to free.
 * @size: The size of the words array.
 */
void free_words_array(char **words, int size)
{
int i = 0;
for (i = 0; i < size; i++)
free(words[i]);
free(words);
}
