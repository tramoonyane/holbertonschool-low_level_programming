#include "main.h"
#include <unistd.h>
#include <stdlib.h>
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
 * strtow - Splits a string into words.
 * @str: The string to split.
 * Return: Returns a pointer to an array of strings (words).
 */
char **strtow(char *str)
{
if (str == NULL || str[0] == '\0')
return (NULL);
int word_count = count_words(str);
char **words = (char **)malloc(sizeof(char *) * (word_count + 1));
if (words == NULL)
return (NULL);
int i = 0, j = 0;
while (str[i] != '\0')
{
if (str[i] != ' ')
{
int word_len = 0;
int k = i;
while (str[k] != ' ' && str[k] != '\0')
{
word_len++;
k++;
}
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
else
{
i++;
}
}
words[j] = NULL;
return (words);
}
