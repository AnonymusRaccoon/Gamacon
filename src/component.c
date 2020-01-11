/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "component.h"
#include "components/transform_component.h"
#include "components/movable_component.h"
#include "components/renderer.h"
#include "components/parallax_component.h"
#include "utility.h"
#include <stdlib.h>

const void *engine_get_component(gc_engine *engine, const char *name)
{
    for (gc_list *cmp = engine->components; cmp; cmp = cmp->next) {
        if (!my_strcmp(((const gc_component *)cmp->data)->name, name))
            return (cmp->data);
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

gc_component *component_remove(gc_component *cmp, const char *name)
{
    for (; cmp; cmp = cmp->next) {
        if (my_strcmp(cmp->name, name))
            continue;
        if (cmp->prev)
            cmp->prev->next = cmp->next;
        if (cmp->next)
            cmp->next->prev = cmp->prev;
        return (cmp);
    }
    return (NULL);
}