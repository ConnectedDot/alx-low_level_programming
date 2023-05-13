#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads a text file and prints it to POSIX stdout.
 *
 * @filename: A pointer to the name of the file.
 * @letters: The number of letters the function should read and print.
 *
 * Return: If the function fails or filename is NULL - 0. Otherwise,
 *         the actual number of bytes the function can read and print.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int fd;
    ssize_t o_bytes = 0, r_bytes = 0, w_bytes = 0;
    char *buffer;

    if (filename == NULL)
        return (0);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    buffer = malloc(sizeof(char) * letters);
    if (buffer == NULL)
    {
        close(fd);
        return (0);
    }

    o_bytes = read(fd, buffer, letters);
    if (o_bytes == -1)
    {
        free(buffer);
        close(fd);
        return (0);
    }

    w_bytes = write(STDOUT_FILENO, buffer, o_bytes);
    if (w_bytes == -1 || w_bytes != o_bytes)
    {
        free(buffer);
        close(fd);
        return (0);
    }

    free(buffer);
    close(fd);

    return (w_bytes);
}
