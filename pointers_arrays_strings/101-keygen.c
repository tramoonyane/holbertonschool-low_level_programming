#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD_LENGTH 10

/**
 * generateRandomPassword - Generates a random password.
 * @password: The buffer to store the generated password.
 * @length: The length of the password to be generated.
 */
void generateRandomPassword(char *password, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        password[i] = charset[index];
    }
    password[length] = '\0';
}

/**
 * generateAndUsePassword - Generates and uses a random password for 101-crackme.
 * This function generates a random password and demonstrates its usage.
 */
void generateAndUsePassword()
{
    char password[PASSWORD_LENGTH + 1]; // +1 for the null-terminator

    // Generate a random password
    generateRandomPassword(password, PASSWORD_LENGTH);

    printf("Generated Password: %s\n", password);

    // Now you can use this password in your 101-crackme program
    // For example, you can pass it as an argument or use it as needed.
}

/**
 * main - The main function that integrates password generation with 101-crackme.
 * This function seeds the random number generator and calls the function to generate and use the password.
 *
 * Return: Always 0.
 */
int main()
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Call the function to generate and use the password
    generateAndUsePassword();

    return 0;
}
