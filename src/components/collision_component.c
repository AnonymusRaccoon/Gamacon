/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** collision_component
*/

#include "xml.h"
#include "component.h"
#include "components/collision_component.h"
#include "utility.h"
#include <stdlib.h>

static void ctr(void *component, va_list args)
{
    struct collision_component *cmp = (struct collision_component *)component;

    cmp->distance_down = 1024;
    cmp->distance_top = 1024;
    cmp->distance_left = 1024;
    cmp->distance_right = 1024;
    cmp->layer = va_arg(args, int);
    cmp->on_collide = NULL;
    cmp->collide_size = 0;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct collision_component *cmp = (struct collision_component *)component;
    cmp->distance_down = 1024;
    cmp->distance_top = 1024;
    cmp->distance_left = 1024;
    cmp->distance_right = 1024;
    cmp->layer = xml_getbinaprop(n, "layer");
    cmp->on_collide = NULL;
    cmp->collide_size = 0;
    (void)scene;
    (void)entity;
}

static void dtr(void *component)
{
    struct collision_component *cmp = (struct collision_component *)component;

    if (cmp->on_collide)
        free(cmp->on_collide);
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

void add_on_collide(struct collision_component *col, collide_listener list)
{
    int old = col->collide_size;

    col->collide_size += sizeof(list);
    col->on_collide = my_realloc(col->on_collide, old, col->collide_size);
    if (!col->on_collide) {
        col->collide_size = 0;
        return;
    }
    col->on_collide[old / sizeof(void (*)())] = list;
}

const struct collision_component collision_component = {
    base: {
        name: "collision_component",
        size: sizeof(struct collision_component),
        dependencies: (char *[]){"collision_component", NULL},
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};