#include "main.h"
#include <stdio.h>

/**
 * print_buffer - Prints the content of a buffer in a specific format.
 * @b: The buffer to be printed.
 * @size: The number of bytes to be printed from the buffer.
 *
 * Description:
 * - The function prints the content of a buffer with a specific format.
 * - Each line starts with the position of the first byte in hexadecimal.
 * - Hexadecimal content is displayed, with two bytes separated by a space.
 * - Printable characters are shown as characters; others are displayed as dots.
 * - Each line ends with a newline character.
 * - If size is 0 or less, the output consists of a newline character only.
 *
 * Return: No return value.
 */
void print_buffer(char *b, int size)
{
    if (size <= 0)
    {
        printf("\n");
        return;
    }

    for (int i = 0; i < size; i += 10)
    {
        printf("%08x: ", i);
        for (int j = 0; j < 10; j++)
        {
            if (i + j < size)
                printf("%02x%c", b[i + j], j % 2 == 1 ? ' ' : '\0');
            else
                printf("  ");
        }

        printf(" ");

        for (int j = 0; j < 10; j++)
        {
            if (i + j < size)
                printf("%c", (b[i + j] >= 32 && b[i + j] <= 126) ? b[i + j] : '.');
            else
                printf(" ");
        }

        printf("\n");
    }
}

/**
 * main - Entry point of the program.
 *
 * Description:
 * - The main function demonstrates the usage of the print_buffer function.
 * - It initializes a character buffer, calculates its size, and then calls
 *   print_buffer to print the buffer's content in a specific format.
 *
 * Return: 0 to indicate successful execution.
 */
int main(void)
{
    char buffer[] = "This is a string!\nAnd this is the rest of the #buffer :)";
    int size = sizeof(buffer) - 1;
    print_buffer(buffer, size);
    return (0);
}
