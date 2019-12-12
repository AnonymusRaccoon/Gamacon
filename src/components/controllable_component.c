/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** controllable_component
*/

#include "xml.h"
#include "component.h"
#include "components/controllable_component.h"
#include "utility.h"
#include <stdlib.h>

static void controllable_ctr(void *component, va_list args)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    cmp->left_key = va_arg(args, int);
    cmp->right_key = va_arg(args, int);
    cmp->jump_key = va_arg(args, int);
}

static void controllable_fdctr(gc_engine *engine, void *component, node *n)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    cmp->left_key = xml_getintprop(n, "left");
    cmp->right_key = xml_getintprop(n, "right");
    cmp->jump_key = xml_getintprop(n, "jump");
    (void)engine;
}

static void controllable_dtr(void *component)
{
    (void)component;
}

static char *controllable_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct controllable_component controllable_component = {
    base: {
        name: "ControllableComponent",
        size: sizeof(struct controllable_component),
        dependencies: (char *[]){
            "MovableComponent", 
            "TransformComponent", 
            NULL
        },
        ctr: &controllable_ctr,
        fdctr: &controllable_fdctr,
        dtr: &controllable_dtr,
        serialize: &controllable_serialize,
        destroy: &component_destroy
    },
    left_key: 16,
    right_key: 3,
    jump_key: ' ',
};