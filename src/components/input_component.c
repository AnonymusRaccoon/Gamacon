/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** input_component
*/

#include "xml.h"
#include "entity.h"
#include "scene.h"
#include "components/input_component.h"

static void ctr(void *component, va_list args)
{
    struct input_component *cmp = (struct input_component *)component;

    cmp->value = 0;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct input_component *cmp = (struct input_component *)component;

    cmp->value = 0;
    (void)scene;
    (void)entity;
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

const struct input_component input_component = {
    base: {
        name: "input_component",
        size: sizeof(struct input_component),
        dependencies: (char *[]){ NULL },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    },
    value: 0
};