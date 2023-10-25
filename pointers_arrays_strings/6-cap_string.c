/**
 * is_separator - Checks if a character is a word separator.
 * @c: The character to check.
 *
 * Return: 1 if c is a separator, 0 otherwise.
 */
int is_separator(char c)
{
  char separators[] = " \t\n,;.!?\"(){}";
  int i;

  for (i = 0; separators[i]; i++)
    {
      if (c == separators[i])
	return 1;
    }

  return 0;
}

/**
 * cap_string - Capitalizes all letters of each word in a string.
 * @str: The input string.
 *
 * Return: Pointer to the modified string.
 */
char *cap_string(char *str)
{
  int i = 0;

  while (str[i] != '\0')
    {
      // Check if the current character is a word separator
      if (is_separator(str[i]))
        {
	  i++; // Move to the next character

	  // Skip multiple consecutive separators
	  while (is_separator(str[i]))
            {
	      i++;
            }
        }
      else
        {
	  // Capitalize all letters of the word
	  while (str[i] != '\0' && !is_separator(str[i]))
            {
	      if (str[i] >= 'a' && str[i] <= 'z')
                {
		  str[i] = str[i] - 32; // Convert to uppercase
                }
	      i++; // Move to the next character
            }
        }
    }

  return str;
}
