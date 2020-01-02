/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#include "xml.h"
#include "component.h"
#include "components/movable_component.h"
#include "utility.h"
#include <stdlib.h>

static void movable_ctr(void *component, va_list args)
{
    struct movable_component *cmp = (struct movable_component *)component;

    cmp->acceleration.x = 0;
    cmp->acceleration.y = 0;
    cmp->velocity.x = 0;
    cmp->velocity.y = 0;
    (void)args;
}

static void movable_fdctr(gc_scene *scene, void *component, node *n)
{
    (void)component;
    (void)n;
    (void)scene;
}

static void movable_dtr(void *component)
{
    (void)component;
}

static char *movable_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct movable_component movable_component = {
    base: {
        name: "movable_component",
        size: sizeof(struct movable_component),
        dependencies: (char *[]){"transform_component", NULL},
        ctr: &movable_ctr,
        fdctr: &movable_fdctr,
        dtr: &movable_dtr,
        serialize: &movable_serialize,
        destroy: &component_destroy
    }
};