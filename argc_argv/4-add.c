#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
* main - Entry point of the program
* @argc: The number of command-line arguments
* @argv: An array of command-line argument strings
* Return: 0 if successful, 1 on error
*/
int main(int argc, char *argv[])
{
int sum = 0;
int i;
if (argc == 1)
{
printf("0\n");
return (0);
}
for (int i = 1; i < argc; i++)
{
char *input = argv[i];
int j = 0;
while (input[j] != '\0')
{
if (!isdigit(input[j]))
{
printf("Error\n");
return (1);
}
j++;
}
sum += atoi(input);
}
printf("%d\n", sum);
return (0);
}
