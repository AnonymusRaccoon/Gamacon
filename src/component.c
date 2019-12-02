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
    Component *base = (Component *)component;
    void *new_cmp = malloc(base->size);
    va_list args;

    *(Component *)new_cmp = *base;
    if (((Component *)new_cmp)->ctr) {
        va_start(args, component);
        ((Component *)new_cmp)->ctr(new_cmp, args);
        va_end(args);
    }
    return (new_cmp);
}