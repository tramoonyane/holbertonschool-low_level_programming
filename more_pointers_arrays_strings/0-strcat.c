/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string to which src will be appended.
 * @src: The source string that will be appended to dest.
 *
 * Return: A pointer to the resulting string (dest).
 */
char *_strcat(char *dest, char *src) {
    char *originalDest = dest;

    // Move the dest pointer to the end of the string
    while (*dest != '\0') {
        dest++;
    }

    // Copy the characters from src to dest
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    // Add a null-terminating character at the end
    *dest = '\0';

    return originalDest; // Return a pointer to the resulting string
}
