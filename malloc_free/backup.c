#include "main.h"
#include <stdlib.h>

/**
 * count_words - Counts the number of words in a string.
 * @str: The input string to count words from.
 * Return: The number of words in the string.
 */
int count_words(char *str)
{
    int count = 0, i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
            count++;
    }

    return count;
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
        while (*str && *str == ' ')
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
            while (word_index-- > 0)
                free(word_array[word_index]);

            free(word_array);
            return (NULL);
        }

        for (i = 0; i < len; i++)
            word[i] = str[i];

        word[len] = '\0';
        word_array[word_index++] = word;
        str = end;
    }

    word_array[word_index] = NULL;
    return (word_array);
}
