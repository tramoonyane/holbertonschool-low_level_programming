#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * is_digit - checks if a string contains a non-digit char
 * @s: string to be evaluated
 *
 * Return: 0 if a non-digit is found, 1 otherwise
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
 * errors - handles errors for main
 */
void errors(void)
{
printf("Error\n");
exit(98);
}

/**
 * multiply_numbers - multiplies two positive numbers represented as strings
 * @s1: first number
 * @s2: second number
 * @result: array to store the result
 * @len: length of the result array
 */
void multiply_numbers(char *s1, char *s2, int *result, int len)
{
int len1, len2, i, carry, digit1, digit2;
len1 = _strlen(s1);
len2 = _strlen(s2);

for (i = 0; i < len; i++)
{
result[i] = 0;
}
for (len1 = len1 - 1; len1 >= 0; len1--)
{
digit1 = s1[len1] - '0';
carry = 0;
for (len2 = len2 - 1; len2 >= 0; len2--)
{
digit2 = s2[len2] - '0';
carry += result[len1 + len2 + 1] + (digit1 *digit2);
result[len1 + len2 + 1] = carry % 10;
carry /= 10;
}
if (carry > 0)
{
result[len1 + len2 + 1] += carry;
}
}
}

/**
 * print_result - prints the result array
 * @result: array to print
 * @len: length of the array
 */
void print_result(int *result, int len)
{
int i, a = 0;
for (i = 0; i < len - 1; i++)
{
if (result[i])
{
a = 1;
_putchar(result[i] + '0');
}
}
if (!a)
{
_putchar('0');
}
_putchar('\n');
}

/**
 * main - entry point of the program
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: always 0 (Success)
 */
int main(int argc, char *argv[])
{
char *s1, *s2;
int len1, len2, len, *result;

if (argc != 3 || !is_digit(argv[1]) || !is_digit(argv[2]))
{
errors();
}
s1 = argv[1];
s2 = argv[2];
len1 = _strlen(s1);
len2 = _strlen(s2);
len = len1 + len2 + 1;
result = malloc(sizeof(int) * len);
if (!result)
{
return (1);
}
multiply_numbers(s1, s2, result, len);
print_result(result, len);
free(result);
return (0);
}
