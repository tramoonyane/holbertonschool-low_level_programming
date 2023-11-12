#include "main.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * main - Entry point of the program.
 *
 * Description: Multiplies two positive numbers provided as command line
 * arguments and prints the result.
 *
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 *
 * Return: 0 on success, 98 on failure.
 */
int main(int argc, char *argv[])
{
	char *num1 = argv[1];
	char *num2 = argv[2];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
		exit(98);
	}

	if (*num1 == '0' || *num2 == '0')
	{
		printf("0\n");
	}
	else
	{
		mul(num1, num2);
	}

	return (0);
}
/**
 * mul - Multiplies two numbers represented as strings.
 * Description: This function takes two strings representing numbers,
 * multiplies them, and prints the result.
 * @s1: The first input number as a string.
 * @s2: The second input number as a string.
 */
void mul(char *s1, char *s2)
{
	int i, l1, l2, total_l, f_digit, s_digit, res = 0, tmp;
	char *ptr;
	void *temp;
	/* Calculate lengths of input strings */
	l1 = 0;
	while (s1[l1] != '\0')
		l1++;
	l2 = 0;
	while (s2[l2] != '\0')
		l2++;
	tmp = l2;
	total_l = l1 + l2;
	ptr = _calloc(sizeof(int), total_l);
	temp = ptr;
	for (l1--; l1 >= 0; l1--)
	{
		f_digit = s1[l1] - '0';
		res = 0;
		l2 = tmp;
		for (l2--; l2 >= 0; l2--)
		{
			s_digit = s2[l2] - '0';
			res += ptr[l2 + l1 + 1] + (f_digit * s_digit);
			ptr[l1 + l2 + 1] = res % 10;
			res /= 10;
		}
		if (res)
			ptr[l1 + l2 + 1] = res % 10;
	}
	while (*ptr == 0)
	{
		ptr++;
		total_l--;
	}
	for (i = 0; i < total_l; i++)
		printf("%i", ptr[i]);
	printf("\n");
	/* Free dynamically allocated memory */
	free(temp);
}
/**
 * _calloc - Allocates memory for an array and initializes it to zero.
 *
 * Description: This function dynamically allocates memory for an array of
 * a specified size and initializes all its elements to zero.
 *
 * @nmemb: Number of elements in the array.
 * @size: Size of each element in bytes.
 *
 * Return: A pointer to the allocated memory, or NULL if allocation fails.
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	_memset(ptr, 0, nmemb * size);

	return (ptr);
}
/**
 * _memset - Fills a block of memory with a constant byte.
 *
 * Description: This function fills the first n bytes of the memory
 * area pointed to by s with the constant byte b.
 *
 * @s: Pointer to the memory block.
 * @b: Value to be set.
 * @n: Number of bytes to be set to the value.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}
