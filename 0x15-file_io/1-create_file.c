#include "main.h"

/**
 * create_file - Creates a file.
 * @filename: A pointer to the name of the file to create.
 * @text_contents: A pointer to a string to write to the file.
 *
 * Return: If the function fails - -1.
 *         Otherwise - 1.
 */
int create_file(const char *filename, char *text_contents)
{
    int o, w, len = 0;

    if (filename == NULL)
        return (-1);

    if (text_contents != NULL)
    {
        for (len = 0; text_contents[len];)
            len++;
    }

    o = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
    w = write(o, text_contents, len);

    if (o == -1 || w == -1)
        return (-1);

    close(o);

    return (1);
}