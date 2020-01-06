/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** friction_component
*/

#include "xml.h"
#include "component.h"
#include "components/friction_component.h"
#include "components/friction_giver.h"
#include "components/collision_component.h"
#include "utility.h"
#include <stdlib.h>

static void on_collide(gc_engine *engine, gc_entity *entity, int id)
{
    struct friction_component *fric = GETCMP(friction_component);
    struct friction_giver *f = GETCOLCMP(friction_giver);

    if (!f)
        return;
    fric->value = f->value;
}

static void ctr(void *component, va_list args)
{
    struct friction_component *cmp = (struct friction_component *)component;

    cmp->value = va_arg(args, int);
    cmp->default_value = cmp->value;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct friction_component *cmp = (struct friction_component *)component;
    struct collision_component *col = GETCMP(collision_component);

    cmp->value = xml_getfloatprop(n, "value");
    cmp->default_value = cmp->value;
    if (!col)
        return ((void)my_printf("Collision not yet setup, you should place the \
friction component after the collision component.\n"));
    add_on_collide(col, &on_collide);
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

const struct friction_component friction_component = {
    base: {
        name: "friction_component",
        size: sizeof(struct friction_component),
        dependencies: (char *[]){
            "movable_component",
            "transform_component",
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