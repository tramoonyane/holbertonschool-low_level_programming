#include <stdio.h>

int main(void)
{
int a[] = {0, 1, 2, 3, 4};
int *p;

p = a;

/* Not allowed to use the variable a
* Not allowed to modify the variable p
* only write one statement
* not allowed to use ,
* not allowed to code anything else
* than the line of expected line of code
* at the expected line
* before the ;
*/
*p = (int[]){98};
  
printf("a[2] = %d\n", a[2]);

return (0);
}
