/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** position_component
*/

#include "component.h"
#include "components/position_component.h"
#include "utility.h"
#include <stddef.h>

void position_ctr(void *component, va_list args)
{
    struct position_component *cmp = (struct position_component *)component;

    cmp->position = va_arg(args, vector2);
}

void position_fdctr(void *component, char *args)
{
    struct position_component *cmp = (struct position_component *)component;

    cmp->position.x = parse_int(&args);;
    cmp->position.y = parse_int(&args);;
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
    fdctr: &position_fdctr,
    dtr: NULL,
    serialize: &position_serialize,
    tostr: NULL
};