#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>
/**
 * print_all - prints different types of arguments based on the format provided
 * @format: a string containing format specifiers for the arguments
 *          'c' - character
 *          'i' - integer
 *          'f' - float
 *          's' - string (if NULL, prints "(nil)")
 *          Any other character is ignored
 * @...: variable number of arguments corresponding to the format
 *
 * This function prints different types of arguments based on the format string
 * provided. It iterates through the format string and prints the arguments
 * according to the specified format character. If the format character is 's'
 * and the corresponding argument is NULL, it prints "(nil)".
 *
 * Return: void (prints to stdout)
 */
void print_all(const char * const format, ...)
{
va_list args;
unsigned int i = 0;
char *str;
char format_char;

va_start(args, format);
while (format && format[i])
{
format_char = format[i];
if (i > 0)
printf(", ");
switch (format_char)
{
case 'c':
printf("%c", va_arg(args, int));
break;
case 'i':
printf("%d", va_arg(args, int));
break;
case 'f':
printf("%f", va_arg(args, double));
break;
case 's':
str = va_arg(args, char *);
if (str == NULL)
printf("(nil)");
else
printf("%s", str);
break;
default:
i++;
continue;
}
i++;
}
printf("\n");
va_end(args);
}
