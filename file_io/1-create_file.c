#include "main.h"
#include <fcntl.h>
#include <unistd.h>

#define PERMISSIONS (S_IRUSR | S_IWUSR) // rw-------

/**
 * create_file - creates a file and writes text_content to it
 * @filename: the name of the file to create
 * @text_content: a NULL terminated string to write to the file
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
int file_descriptor, write_status, close_status;

    if (filename == NULL)
        return -1;

    file_descriptor = open(filename, O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
    if (file_descriptor == -1)
        return -1;

    if (text_content != NULL) {
        write_status = write(file_descriptor, text_content, strlen(text_content));
        if (write_status == -1) {
            close(file_descriptor);
            return -1;
        }
    }

    close_status = close(file_descriptor);
    if (close_status == -1)
        return -1;

    return 1;
}
