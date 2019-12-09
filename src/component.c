/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "component.h"
#include "components/transform_component.h"
#include "components/movable_component.h"
#include "components/texture_renderer.h"
#include "components/parallax_component.h"
#include "utility.h"
#include <stdlib.h>

const void *get_component(char *name)
{
    static const void *all_components[] = {
        &transform_component,
        &movable_component,
        &texture_renderer,
        &parallax_component,
        NULL
    };

    for (int i = 0; all_components[i]; i++) {
        if (!my_strcmp(((const gc_component *)all_components[i])->name, name))
            return (all_components[i]);
    }
    return (NULL);
}

void *new_component(const void *component, ...)
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

void component_destroy(void *component)
{
    gc_component *cmp = (gc_component *)component;
    if (cmp->dtr)
        cmp->dtr(component);
    free(component);
}