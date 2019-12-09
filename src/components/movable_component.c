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

    cmp->left_key = va_arg(args, int);
    cmp->right_key = va_arg(args, int);
    cmp->jump_key = va_arg(args, int);
}

static void movable_fdctr(gc_engine *engine, void *component, node *n)
{
    struct movable_component *cmp = (struct movable_component *)component;

    cmp->left_key = xml_getproperty(n, "left")[0];
    cmp->right_key = xml_getproperty(n, "right")[0];
    cmp->jump_key = xml_getproperty(n, "jump")[0];
    (void)engine;
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
        name: "MovableComponent",
        size: sizeof(struct movable_component),
        dependencies: (char *[]){NULL},
        ctr: &movable_ctr,
        fdctr: &movable_fdctr,
        dtr: &movable_dtr,
        serialize: &movable_serialize,
        destroy: &component_destroy
    },
    left_key: 'Q',
    right_key: 'D',
    jump_key: ' '
};