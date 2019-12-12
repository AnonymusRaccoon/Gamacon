/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** collision_component
*/

#include "xml.h"
#include "component.h"
#include "components/collision_component.h"
#include "utility.h"
#include <stdlib.h>

static void collision_ctr(void *component, va_list args)
{
    struct collision_component *cmp = (struct collision_component *)component;

    cmp->layer = va_arg(args, int);
}

static void collision_fdctr(gc_engine *engine, void *component, node *n)
{
    struct collision_component *cmp = (struct collision_component *)component;

    cmp->layer = xml_getintprop(n, "layer");
    (void)engine;
}

static void collision_dtr(void *component)
{
    (void)component;
}

static char *collision_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct collision_component collision_component = {
    base: {
        name: "CollisionComponent",
        size: sizeof(struct collision_component),
        dependencies: (char *[]){"TransformComponent", NULL},
        ctr: &collision_ctr,
        fdctr: &collision_fdctr,
        dtr: &collision_dtr,
        serialize: &collision_serialize,
        destroy: &component_destroy
    },
    layer: 0
};