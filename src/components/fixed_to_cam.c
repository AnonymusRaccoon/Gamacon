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
#include <components/renderer.h>

static void ctr(void *component, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    struct renderer *rend;
    struct fixed_to_cam *cmp = (struct fixed_to_cam *)component;

    if (!entity)
        return;
    cmp->pos = va_arg(args, gc_vector2);
    cmp->per_x = va_arg(args, int);
    cmp->per_y = va_arg(args, int);
    cmp->size_x = va_arg(args, int);
    cmp->size_y = va_arg(args, int);
    cmp->per_w = va_arg(args, int);
    cmp->per_h = va_arg(args, int);
    if (!(rend = GETCMP(entity, renderer)))
        my_printf("Missing a renderer on an entity fixed to the cam.\n");
    else if (va_arg(args, int)) {
        rend->render_mode_x = RENDER_MODE_CENTERED;
        if (rend->type != GC_TXTREND)
            rend->render_mode_y = RENDER_MODE_CENTERED;
    }
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct fixed_to_cam *cmp = (struct fixed_to_cam *)component;
    struct renderer *rend = GETCMP(entity, renderer);

    cmp->pos.x = xml_getintprop(n, "x");
    cmp->pos.y = xml_getintprop(n, "y");
    cmp->per_x = xml_propcontains(n, "x", "%");
    cmp->per_y = xml_propcontains(n, "y", "%");
    cmp->size_x = xml_getintprop(n, "width");
    cmp->per_w = xml_propcontains(n, "width", "%");
    cmp->size_y = xml_getintprop(n, "height");
    cmp->per_h = xml_propcontains(n, "height", "%");
    if (!rend)
        my_printf("Missing a renderer on an entity fixed to the cam.\n");
    else {
        rend->render_mode_x = RENDER_MODE_CENTERED;
        rend->render_mode_y = RENDER_MODE_CENTERED;
    }
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
    pos: (gc_vector2){0, 0},
    per_x: false,
    per_y: false,
    per_w: false,
    size_x: 0,
    size_y: 0,
    per_h: false
};