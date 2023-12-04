#include "main.h"
#include <fcntl.h>

/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 * @filename: the name of the file to read
 * @letters: number of letters to read and print
 * Return: number of letters read and printed, 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters) {
    ssize_t file_descriptor, bytes_read, bytes_written;
    char *buffer;

    if (filename == NULL)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
        return 0;

    buffer = malloc(sizeof(char) * letters);
    if (buffer == NULL) {
        close(file_descriptor);
        return 0;
    }

    bytes_read = read(file_descriptor, buffer, letters);
    if (bytes_read == -1) {
        free(buffer);
        close(file_descriptor);
        return 0;
    }

    bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
    if (bytes_written == -1 || bytes_written != bytes_read) {
        free(buffer);
        close(file_descriptor);
        return 0;
    }

    free(buffer);
    close(file_descriptor);

    return bytes_written;
}
