/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** friction_component
*/

#include "xml.h"
#include "component.h"
#include "components/friction_component.h"
#include "utility.h"
#include <stdlib.h>

static void fric_ctr(void *component, va_list args)
{
    struct friction_component *cmp = (struct friction_component *)component;

    cmp->value = va_arg(args, int);
    cmp->threshold = va_arg(args, int);
}

static void fric_fdctr(gc_engine *engine, void *component, node *n)
{
    struct friction_component *cmp = (struct friction_component *)component;

    cmp->value = xml_getintprop(n, "value");
    cmp->threshold = xml_getintprop(n, "threshold");
    (void)engine;
}

static void fric_dtr(void *component)
{
    (void)component;
}

static char *fric_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct friction_component friction_component = {
    base: {
        name: "friction_component",
        size: sizeof(struct friction_component),
        dependencies: (char *[]){
            "movable_component",
            "transform_component",
            NULL
        },
        ctr: &fric_ctr,
        fdctr: &fric_fdctr,
        dtr: &fric_dtr,
        serialize: &fric_serialize,
        destroy: &component_destroy
    },
    value: 10,
    threshold: 1
};