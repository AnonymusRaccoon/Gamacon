/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** my_realloc
*/

#include <malloc.h>
#include <stddef.h>

void *my_realloc(void *oldptr, size_t oldsize, size_t newsize)
{
    void *new = malloc(newsize);

    if (oldptr && new) {
        for (size_t i = 0; i < oldsize && i < newsize; i++) {
            ((char *)new)[i] = ((char *)oldptr)[i];
        }
    }
    if (oldptr)
        free(oldptr);
    return (new);
}