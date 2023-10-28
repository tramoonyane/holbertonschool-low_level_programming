#include "main.h"

/**
* infinite_add - Adds two numbers represented as strings and stores the result.
* @n1: The first number as a string.
* @n2: The second number as a string.
* @r: The buffer to store the result.
* @size_r: The size of the buffer.
*
* Return: A pointer to the result if it fits in the buffer;
* otherwise, return 0.
*/
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
int len1 = 0, len2 = 0, carry = 0;
int i, j, k;
while (n1[len1])
len1++;
while (n2[len2])
len2++;
if (len1 + len2 + 1 > size_r)
return (0);
i = len1 - 1;
j = len2 - 1;
k = size_r - 1;
r[k] = '\0';
while (i >= 0 || j >= 0 || carry)
{
int sum = carry;
if (i >= 0)
sum += n1[i] - '0';
if (j >= 0)
sum += n2[j] - '0';
carry = sum / 10;
r[--k] = (sum % 10) + '0';
if (i >= 0)
i--;
if (j >= 0)
j--;
}
if (k == 0)
{
return (0);
}
for (i = 0; r[k]; i++, k++)
{
r[i] = r[k];
}
r[i] = '\0';
return (r);
}
