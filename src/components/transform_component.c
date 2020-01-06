/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** position_component
*/

#include "component.h"
#include "xml.h"
#include "components/transform_component.h"
#include "utility.h"
#include <stddef.h>

static void ctr(void *component, va_list args)
{
    struct transform_component *cmp = (struct transform_component *)component;

    cmp->position = va_arg(args, gc_vector2);
    cmp->size = va_arg(args, gc_vector2);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct transform_component *cmp = (struct transform_component *)component;
    node *pos = xml_getnode(n, "Position");
    node *size = xml_getnode(n, "Size");

    if (pos) {
        cmp->position.x = xml_getintprop(pos, "x");
        cmp->position.y = xml_getintprop(pos, "y");
    } else {
        cmp->position.x = 0;
        cmp->position.y = 0;
    }
    if (size) {
        cmp->size.x = xml_getintprop(size, "x");
        cmp->size.y = xml_getintprop(size, "y");
    } else {
        cmp->size.x = 0;
        cmp->size.y = 0;
    }
    (void)scene;
    (void)entity;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct transform_component transform_component = {
    base: {
        name: "transform_component",
        size: sizeof(struct transform_component),
        dependencies: (char *[]){NULL},
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: NULL,
        serialize: &serialize,
        destroy: &component_destroy
    },
    position: {0, 0},
    size: {0, 0}
};