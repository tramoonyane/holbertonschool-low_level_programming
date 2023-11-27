#include "lists.h"
#include "stdio.h"
#include "stddef.h"

/**
 * print_list - prints all the elements of a list_t list
 * @h: pointer to the head of the list
 *
 * Return: the number of nodes
 */
size_t print_list(const list_t *h)
{
const list_t *current = h;
size_t node_count = 0;

while (current != NULL)
{
if (current->str == NULL)
printf("[0] (nil)\n");
else
printf("[%u] %s\n", current->len, current->str);
node_count++;
current = current->next;
}
return (node_count);
}
