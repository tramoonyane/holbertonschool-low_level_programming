#include "main.h"
#include <stdlib.h>

/**
 * _strlen - calculates the length of a string
 * @s: the input string
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * is_digit - checks if a string is composed of digits
 * @s: the input string
 *
 * Return: 1 if composed of digits, 0 otherwise
 */
int is_digit(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _calloc - allocates memory for an array
 * @nmemb: number of elements
 * @size: size of each element
 *
 * Return: pointer to the allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);

	for (i = 0; i < (nmemb * size); i++)
		ptr[i] = 0;

	return (ptr);
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 98 on failure
 */
int main(int argc, char *argv[])
{
	int len1, len2, len_res, i, j, mul, carry = 0;
	int *result;

	if (argc != 3)
		exit(98);

	len1 = _strlen(argv[1]);
	len2 = _strlen(argv[2]);

	if (!is_digit(argv[1]) || !is_digit(argv[2]))
		exit(98);

	len_res = len1 + len2;
	result = _calloc(len_res, sizeof(*result));

	for (i = len1 - 1; i >= 0; i--)
	{
		carry = 0;
		for (j = len2 - 1; j >= 0; j--)
		{
			mul = (argv[1][i] - '0') * (argv[2][j] - '0');
			mul += result[i + j + 1] + carry;
			carry = mul / 10;
			result[i + j + 1] = mul % 10;
		}
		result[i + j + 1] = carry;
	}

	if (result[0] == 0)
		i = 1;
	else
		i = 0;

	for (; i < len_res; i++)
	{
		_putchar(result[i] + '0');
	}
	_putchar('\n');
	free(result);
	return (0);
}
