/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#include "component.h"
#include "Components/movable_component.h"
#include <stdlib.h>

static void movable_ctr(void *component, va_list args)
{
    struct MovableComponent *movable = (struct MovableComponent *)component;

    movable->left_key = va_arg(args, int);
    movable->right_key = va_arg(args, int);
    movable->jump_key = va_arg(args, int);
}

static void movable_dtr(void *component)
{
    Component *base = (Component *)component;

    if (base->tostr)
        free(base->tostr);
}

static char *movable_serialize(void *component)
{
    //Component *base = (Component *)component;
    (void)component;
    return (NULL);
}

const Component MovableComponent =  {
    name: "PositionComponent",
    size: sizeof(MovableComponent),
    dependencies: NULL,
    ctr: &movable_ctr,
    dtr: &movable_dtr,
    serialize: &movable_serialize,
    tostr: NULL
};