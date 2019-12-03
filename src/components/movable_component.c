/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

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

static void movable_fdctr(void *component, char *args)
{
    struct movable_component *cmp = (struct movable_component *)component;

    cmp->left_key = parse_int(&args);
    cmp->right_key = parse_int(&args);
    cmp->jump_key = parse_int(&args);
}

static void movable_dtr(void *component)
{
    gc_component *base = (gc_component *)component;

    if (base->tostr)
        free(base->tostr);
}

static char *movable_serialize(void *component)
{
    //Component *base = (Component *)component;
    (void)component;
    return (NULL);
}

const gc_component movable_component = {
    name: "MovableComponent",
    size: sizeof(struct movable_component),
    dependencies: NULL,
    ctr: &movable_ctr,
    fdctr: &movable_fdctr,
    dtr: &movable_dtr,
    serialize: &movable_serialize,
    tostr: NULL
};