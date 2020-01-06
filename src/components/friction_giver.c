/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** friction_giver
*/

#include "xml.h"
#include "entity.h"
#include "scene.h"
#include "components/friction_giver.h"

static void ctr(void *component, va_list args)
{
    struct friction_giver *cmp = (struct friction_giver *)component;

    cmp->value = va_arg(args, double);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct friction_giver *cmp = (struct friction_giver *)component;

    cmp->value = xml_getfloatprop(n, "value");
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

const struct friction_giver friction_giver = {
    base: {
        name: "friction_giver",
        size: sizeof(struct friction_giver),
        dependencies: (char *[]){
            "transform_component",
            "friction_giver",
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    },
    value: 10
};