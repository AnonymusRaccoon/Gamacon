/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** camera_follow
*/

#include "xml.h"
#include "component.h"
#include "components/fixed_to_cam_component.h"
#include "utility.h"
#include <stdlib.h>

static void ctr(void *component, va_list args)
{
    struct fixed_to_cam *cmp = (struct fixed_to_cam *)component;

    cmp->offset = va_arg(args, gc_vector2);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct fixed_to_cam *cmp = (struct fixed_to_cam *)component;

    n = xml_getnode(n, "Position");
    cmp->offset.x = xml_getintprop(n, "x");
    cmp->offset.y = xml_getintprop(n, "y");
    (void)scene;
    (void)entity;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct fixed_to_cam fixed_to_cam = {
    base: {
        name: "fixed_to_cam",
        size: sizeof(struct fixed_to_cam),
        dependencies: (char *[]){
            "transform_component",
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: NULL,
        serialize: &serialize,
        destroy: &component_destroy
    },
    offset: (gc_vector2){0, 0}
};