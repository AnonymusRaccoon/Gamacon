/*
** EPITECH PROJECT, 2019
** Read a line from a file.
** File description:
** grep
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "read_line.h"

static int indexof(char *str, char c)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            return (i);
    }
    return (-1);
}

static char *concat_line(char *line, char *buffer, int end_index)
{
    int line_length = 0;
    char *str = NULL;
    int ncated = -1;

    if (line)
        while (line[line_length])
            line_length++;
    str = malloc(sizeof(char) * (line_length + end_index + 1));
    if (str == NULL)
        return (NULL);
    for (int i = 0; i < line_length; i++)
        str[i] = line[i];
    for (ncated = 0; ncated < end_index && buffer[ncated]; ncated++)
        str[line_length + ncated] = buffer[ncated];
    str[line_length + ncated] = '\0';
    if (line != 0)
        free(line);
    return (str);
}

static char *handle_sub_lines(char buf[READ_SIZE + 1], char *line, bool *status)
{
    char *str = NULL;
    int index = indexof(buf, '\n');
    int next_index = indexof(buf + index + 1, '\n');

    if (index != -1) {
        if (next_index != -1) {
            buf[index] = '\a';
            *status = 1;
            return (concat_line(line, buf + index + 1, next_index));
        } else
            str = concat_line(line, buf + index + 1, READ_SIZE - 1 - index);
    } else if (line != 0)
        str = line;
    return (str);
}

static char *full_read(int fd, char *line)
{
    static char buffer[READ_SIZE + 1] = {0};
    bool status = 0;
    char *str = handle_sub_lines(buffer, line, &status);
    int count;
    int index;

    if (status == 1)
        return (str);
    count = read(fd, buffer, READ_SIZE);
    buffer[count] = '\0';
    index = indexof(buffer, '\n');
    if (count <= 0 && !str) {
        free(str);
        return (NULL);
    }
    if (index != -1)
        return (concat_line(str, buffer, index));
    else if (count != READ_SIZE)
        return (concat_line(str, buffer, count));
    else
        return (full_read(fd, concat_line(str, buffer, count)));
}

char *read_line(int fd)
{
    return full_read(fd, NULL);
}