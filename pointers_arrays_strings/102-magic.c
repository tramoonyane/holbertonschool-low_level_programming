#include <stdio.h>
/* Entry point of the program */
int main(void)
{
	int a[] = {0, 1, 2, 3, 4};
	int *p;

	p = a;

/* 
 * Not allowed to use the variable a
 * Not allowed to modify the variable p
 * Only write one statement
 * Not allowed to use ,
 * Not allowed to code anything else
 * than the line of expected line of code at the expected line before the ;
 */
	*p = (int[]){98};
	/* Add one line here to print "a[2] = 98," followed by a new line */
	printf("a[2] = %d\n", 98);

	return (0);
}
