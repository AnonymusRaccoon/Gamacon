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
}

static void fdctr(gc_scene *scene, void *component, node *n)
{
    struct collision_component *cmp = (struct collision_component *)component;
    cmp->distance_down = 1024;
    cmp->distance_top = 1024;
    cmp->distance_left = 1024;
    cmp->distance_right = 1024;
    cmp->layer = xml_getbinaprop(n, "layer");
    (void)scene;
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
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