#include <stdio.h>
#include <stdlib.h>

/**
* minCoins - Calculate the minimum number of coins to make change.
* @cents: The amount of cents to make change for.
*
* Return: The minimum number of coins needed.
*/
int minCoins(int cents)
{
int coins[] = {25, 10, 5, 2, 1};
int numCoins = sizeof(coins) / sizeof(coins[0]);
int count = 0;
int i;
if (cents <= 0)
{
return (0);
}
for (i = 0; i < numCoins; i++)
{
while (cents >= coins[i])
{
cents -= coins[i];
count++;
}
}
return (count);
}

/**
* main - Entry point of the program.
* @argc: The number of command-line arguments.
* @argv: An array of strings representing the command-line arguments.
*
* Return: 0 for success, 1 for an error.
*/
int main(int argc, char *argv[])
{
int cents;
int coinsNeeded;
if (argc != 2)
{
printf("Error\n");
return (1);
}
cents = atoi(argv[1]);
if (cents < 0)
{
printf("0\n");
}
else
{
coinsNeeded = minCoins(cents);
printf("%d\n", coinsNeeded);
}
return (0);
}
