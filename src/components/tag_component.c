/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parralax_component
*/

#include "components/tag_component.h"
#include <malloc.h>
#include "xml.h"
#include "components/parallax_component.h"
#include "components/transform_component.h"

static void ctr(void *component, va_list args)
{
    struct tag_component *cmp = (struct tag_component *)component;

    cmp->tag = va_arg(args, char *);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct tag_component *cmp = (struct tag_component *)component;

    cmp->tag = xml_getproperty(n, "tag");
    (void)scene;
    (void)entity;
}

static void dtr(void *component)
{
    struct tag_component *cmp = (struct tag_component *)component;

    free(cmp->tag);
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct tag_component tag_component = {
    base: {
        name: "tag_component",
        size: sizeof(struct tag_component),
        dependencies: (char *[]){NULL},
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    },
    tag: NULL
};