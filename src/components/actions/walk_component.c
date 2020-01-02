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

    cmp->acceleration = va_arg(args, int);
    cmp->max_acceleration = va_arg(args, int);
}

static void walk_fdctr(gc_scene *scene, void *component, node *n)
{
    struct walk_action *cmp = (struct walk_action *)component;

    cmp->acceleration = xml_getintprop(n, "acceleration");
    cmp->max_acceleration = xml_getintprop(n, "max_acceleration");
    (void)scene;
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
    acceleration: 0,
    max_acceleration: 0
};