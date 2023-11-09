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
  int i;
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



#include <stdlib.h>
#include "main.h"

/**
 * count_word - helper function to count the number of words in a string
 * @s: string to evaluate
 *
 * Return: number of words
 */
int count_word(char *s)
{
	int flag, c, w;

	flag = 0;
	w = 0;

	for (c = 0; s[c] != '\0'; c++)
	{
		if (s[c] == ' ')
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			w++;
		}
	}

	return (w);
}
/**
 * **strtow - splits a string into words
 * @str: string to split
 *
 * Return: pointer to an array of strings (Success)
 * or NULL (Error)
 */
char **strtow(char *str)
{
	char **matrix, *tmp;
	int i, k = 0, len = 0, words, c = 0, start, end;

	while (*(str + len))
		len++;
	words = count_word(str);
	if (words == 0)
		return (NULL);

	matrix = (char **) malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (c)
			{
				end = i;
				tmp = (char *) malloc(sizeof(char) * (c + 1));
				if (tmp == NULL)
					return (NULL);
				while (start < end)
					*tmp++ = str[start++];
				*tmp = '\0';
				matrix[k] = tmp - c;
				k++;
				c = 0;
			}
		}
		else if (c++ == 0)
			start = i;
	}

	matrix[k] = NULL;

	return (matrix);
}
