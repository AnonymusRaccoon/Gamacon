/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** walk_action
*/

#include "xml.h"
#include "component.h"
#include "components/controllable_component.h"
#include "components/actions/walk_action.h"
#include "utility.h"
#include <stdlib.h>

static void walk_ctr(void *component, va_list args)
{
    struct walk_action *cmp = (struct walk_action *)component;

    cmp->speed = va_arg(args, int);
    cmp->max_speed = va_arg(args, int);
    cmp->max_acceleration = va_arg(args, int);
}

static void walk_fdctr(gc_engine *engine, void *component, node *n)
{
    struct walk_action *cmp = (struct walk_action *)component;

    cmp->speed = xml_getintprop(n, "speed");
    cmp->max_speed = xml_getintprop(n, "max_speed");
    cmp->max_acceleration = xml_getintprop(n, "max_acceleration");
    (void)engine;
}

static void walk_dtr(void *component)
{
    (void)component;
}

static char *walk_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct walk_action walk_action = {
    base: {
        name: "walk_action",
        size: sizeof(struct walk_action),
        dependencies: (char *[]){
            "controllable_component",
            "movable_component",
            "transform_component",
            NULL
        },
        ctr: &walk_ctr,
        fdctr: &walk_fdctr,
        dtr: &walk_dtr,
        serialize: &walk_serialize,
        destroy: &component_destroy
    },
    speed: 0,
    max_speed: 0,
    max_acceleration: 0
};