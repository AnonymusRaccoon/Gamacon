/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** gravity_component
*/

#include "xml.h"
#include "component.h"
#include "components/gravity_component.h"
#include "utility.h"
#include <stdlib.h>

static void gravity_ctr(void *component, va_list args)
{
    struct gravity_component *cmp = (struct gravity_component *)component;

    cmp->gravity_speed = va_arg(args, int);
}

static void gravity_fdctr(gc_engine *engine, void *component, node *n)
{
    struct gravity_component *cmp = (struct gravity_component *)component;

    cmp->gravity_speed = xml_getintprop(n, "gravity_speed");
    (void)engine;
}

static void gravity_dtr(void *component)
{
    (void)component;
}

static char *gravity_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct gravity_component gravity_component = {
    base: {
        name: "GravityComponent",
        size: sizeof(struct gravity_component),
        dependencies: (char *[]){
            "MovableComponent",
            "TransformComponent",
            NULL
        },
        ctr: &gravity_ctr,
        fdctr: &gravity_fdctr,
        dtr: &gravity_dtr,
        serialize: &gravity_serialize,
        destroy: &component_destroy
    },
    gravity_speed: 10
};