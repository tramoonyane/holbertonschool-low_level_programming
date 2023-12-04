#include "main.h"
#include <fcntl.h>

/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 * @filename: the name of the file to read
 * @letters: number of letters to read and print
 * Return: number of letters read and printed, 0 on failure
 */
#define BUFFER_SIZE 1024

ssize_t read_textfile(const char *filename, size_t letters) {
    ssize_t file_descriptor, bytes_read, bytes_written, total_bytes = 0;
    char buffer[BUFFER_SIZE];

    if (filename == NULL)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
        return 0;

    while ((bytes_read = read(file_descriptor, buffer, BUFFER_SIZE)) > 0 && total_bytes < letters) {
        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if (bytes_written == -1 || bytes_written != bytes_read) {
            close(file_descriptor);
            return total_bytes;
        }
        total_bytes += bytes_written;
        if (total_bytes >= letters)
            break;
    }

    close(file_descriptor);

    return total_bytes;
}
