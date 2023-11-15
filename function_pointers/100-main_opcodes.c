#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - Prints the opcodes of its own main function
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 on success, 1 if incorrect number of arguments, 2 if negative bytes
 */
int main(int argc, char *argv[])
{
int i;
if (argc != 2)
{
write(2, "Error\n", 6);
exit(1);
}
int num_bytes = atoi(argv[1]);
if (num_bytes < 0)
{
write(2, "Error\n", 6);
exit(2);
}
unsigned char *ptr = (unsigned char *)main;
for (i = 0; i < num_bytes; i++)
{
char hex[3];
sprintf(hex, "%02x", *(ptr + i));
write(1, hex, 2);
}
write(1, "\n", 1);
return (0);
}
