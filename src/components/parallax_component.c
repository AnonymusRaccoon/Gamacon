/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parralax_component
*/

#include "xml.h"
#include "components/parallax_component.h"
#include "components/transform_component.h"

static void ctr(void *component, va_list args)
{
    struct parallax_component *cmp = (struct parallax_component *)component;

    cmp->speed = va_arg(args, double);
    cmp->old_pos = (gc_vector2){0, 0};
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct parallax_component *cmp = (struct parallax_component *)component;

    cmp->speed = xml_getfloatprop(n, "speed");
    cmp->old_pos = (gc_vector2){0, 0};
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

const struct parallax_component parallax_component = {
    base: {
        name: "parallax_component",
        size: sizeof(struct parallax_component),
        dependencies: (char *[]){"transform_component", "renderer", NULL},
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    },
    speed: 0.5
};