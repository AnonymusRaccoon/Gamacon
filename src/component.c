/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "component.h"
#include <stdlib.h>

void *new_component(Component *component, ...)
{
    void *new_cmp = malloc(component->size);
    va_list args;

    *(Component *)new_cmp = *component;
    if (((Component *)new_cmp)->ctr) {
        va_start(args, component);
        ((Component *)new_cmp)->ctr(new_cmp, args);
        va_end(args);
    }
    return (new_cmp);
}