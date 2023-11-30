#include "lists.h"

/**
 * before_main - prints specific lines before main function
 */
void before_main(void)
{
char *line1 = "You're beat! and yet, you must allow,\n";
char *line2 = "I bore my house upon my back!\n";

while (*line1)
{
_putchar(*line1);
line1++;
}
while (*line2)
{
_putchar(*line2);
line2++;
}
}
