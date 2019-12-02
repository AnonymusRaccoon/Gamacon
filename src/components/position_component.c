/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** position_component
*/

#include "component.h"
#include "components/position_component.h"
#include <stddef.h>

void position_ctr(void *component, va_list args)
{
    struct position_component *cmp = (struct position_component *)component;

    cmp->position = va_arg(args, vector2);
}

char *position_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const gc_component position_component = {
    name: "PositionComponent",
    size: sizeof(struct position_component),
    dependencies: NULL,
    ctr: &position_ctr,
    dtr: NULL,
    serialize: &position_serialize,
    tostr: NULL
};