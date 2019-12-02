/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "component.h"
#include <stdlib.h>

void *new_component(void *component, ...)
{
    gc_component *base = (gc_component *)component;
    va_list args;
    void *new_cmp = malloc(base->size);

    if (!new_cmp)
        return (NULL);
    *(gc_component *)new_cmp = *base;
    if (((gc_component *)new_cmp)->ctr) {
        va_start(args, component);
        ((gc_component *)new_cmp)->ctr(new_cmp, args);
        va_end(args);
    }
    return (new_cmp);
}