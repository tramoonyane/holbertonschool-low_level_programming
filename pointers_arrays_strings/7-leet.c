/**
* leet - Encodes a string into "1337".
* @str: The input string.
*
* Return: Pointer to the modified string.
*/
char *leet(char *str)
{
char *leet_dict = "aAeEoOtTlL";
char *leet_codes = "44370171";
int i, j;
for (i = 0; str[i] != '\0'; i++)
{
for (j = 0; leet_dict[j] != '\0'; j++)
{
if (str[i] == leet_dict[j])
{
str[i] = leet_codes[j];
break;
}
}
}
return (str);
}
