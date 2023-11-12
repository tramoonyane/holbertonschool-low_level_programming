#include "main.h"
#include <stdlib.h>
#include <stdio.h>

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

	return 0;
}

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

	/* Store the original length of s2 for later use */
	tmp = l2;

	/* Calculate the total length of the result */
	total_l = l1 + l2;

	/* Dynamically allocate memory for the result */
	ptr = _calloc(sizeof(int), total_l);

	/* store our pointer address to free later */
	temp = ptr;

	/* Perform multiplication algorithm */
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

	/* Normalize result by removing leading zeros */
	while (*ptr == 0)
	{
		ptr++;
		total_l--;
	}

	/* Print the final result */
	for (i = 0; i < total_l; i++)
		printf("%i", ptr[i]);
	printf("\n");

	/* Free dynamically allocated memory */
	free(temp);
}

void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;

	if (nmemb == 0 || size == 0)
		return NULL;
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return NULL;
	_memset(ptr, 0, nmemb * size);

	return (ptr);
}

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
