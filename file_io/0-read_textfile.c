#include "main.h"

/**
 * read_textfile - Reads a text file and prints it to the POSIX standard output.
 * @filename: The name of the file to read.
 * @letters: The number of letters it should read and print.
 *
 * Return: The actual number of letters it could read and print, or 0 on failure.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int file_descriptor;
    ssize_t bytes_read, bytes_written;
    char *buffer;
    int newline_flag = 0;  // Flag to check if a newline is printed

    if (filename == NULL)
        return (0);

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
        return (0);

    buffer = malloc(sizeof(char) * letters);
    if (buffer == NULL)
    {
        close(file_descriptor);
        return (0);
    }

    bytes_written = 0;
    do {
        bytes_read = read(file_descriptor, buffer, letters);
        if (bytes_read == -1)
        {
            free(buffer);
            close(file_descriptor);
            return (0);
        }

        if (bytes_read > 0)
        {
            bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
            if (bytes_written != bytes_read)
            {
                free(buffer);
                close(file_descriptor);
                return (0);
            }
            if (buffer[bytes_read - 1] != '\n')
            {
                newline_flag = 0;  // Reset newline_flag if the last character is not a newline
                for (ssize_t i = bytes_read - 1; i >= 0; i--)
                {
                    if (buffer[i] == ' ' || buffer[i] == '\t')
                    {
                        newline_flag = 1;
                        bytes_written += write(STDOUT_FILENO, "\n", 1);
                        break;
                    }
                }
                if (!newline_flag)
                {
                    bytes_written += write(STDOUT_FILENO, "\n", 1);
                }
                if (bytes_written <= 0)
                {
                    free(buffer);
                    close(file_descriptor);
                    return (0);
                }
            }
        }
    } while (bytes_read > 0);

    free(buffer);
    close(file_descriptor);
    return (bytes_written);
}
