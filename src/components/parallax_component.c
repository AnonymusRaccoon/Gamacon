/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parralax_component
*/

#include "xml.h"
#include "components/parallax_component.h"
#include "components/transform_component.h"

static void parallax_ctr(void *component, va_list args)
{
    struct parallax_component *cmp = (struct parallax_component *)component;

    cmp->speed = va_arg(args, double);
}

static void parallax_fdctr(gc_scene *scene, void *component, node *n)
{
    struct parallax_component *cmp = (struct parallax_component *)component;

    cmp->speed = xml_getfloatprop(n, "speed");
    (void)scene;
}

static void parallax_dtr(void *component)
{
    (void)component;
}

static char *parallax_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct parallax_component parallax_component = {
    base: {
        name: "parallax_component",
        size: sizeof(struct parallax_component),
        dependencies: (char *[]){"transform_component", "renderer", NULL},
        ctr: &parallax_ctr,
        fdctr: &parallax_fdctr,
        dtr: &parallax_dtr,
        serialize: &parallax_serialize,
        destroy: &component_destroy
    },
    speed: 0.5
};