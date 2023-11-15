#include <stdio.h>
#include <stdlib.h>
#include <udis86.h>

/**
 * main - Prints the opcodes of its own main function
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 on success, 1 if incorrect number of arguments, 2 if negative bytes
 */
int main(int argc, char *argv[])
{
if (argc != 2)
{
fprintf(stderr, "Error\n");
exit(1);
}
int num_bytes = atoi(argv[1]);
if (num_bytes < 0)
{
fprintf(stderr, "Error\n");
exit(2);
}
unsigned char *ptr = (unsigned char *)main;
ud_t ud_obj;
ud_init(&ud_obj);
ud_set_input_buffer(&ud_obj, ptr, num_bytes);
ud_set_mode(&ud_obj, 64);
ud_set_syntax(&ud_obj, UD_SYN_INTEL);
while (ud_disassemble(&ud_obj))
{
printf("\t%s\n", ud_insn_hex(&ud_obj));
}
return (0);
}
