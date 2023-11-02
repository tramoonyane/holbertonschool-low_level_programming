#include "main.h"
/**
* is_palindrome - Check if a string is a palindrome.
* @s: The string to check.
*
* Return: 1 if the string is a palindrome, 0 otherwise.
*/
int is_palindrome(char *s)
{
if (*s == '\0' || *s == '\n')
return (1);
static int start = 0;
static int end;
if (start == 0)
end = strlen(s) - 1;
if (start >= end)
{
start = 0;
return (1);
}
if (s[start] != s[end])
{
start = 0;
return (0);
}
start++;
end--;
return (is_palindrome(s));
}
