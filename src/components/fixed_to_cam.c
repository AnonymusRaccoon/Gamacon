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
    bool centered;

    if (!entity)
        return;
    rend = GETCMP(entity, renderer);
    cmp->pos = va_arg(args, gc_vector2);
    cmp->per_x = va_arg(args, int);
    cmp->per_y = va_arg(args, int);
    cmp->size_x = va_arg(args, int);
    cmp->size_y = va_arg(args, int);
    cmp->per_w = va_arg(args, int);
    cmp->per_h = va_arg(args, int);
    centered = va_arg(args, int);
    if (!rend)
        my_printf("Missing a renderer on an entity fixed to the cam.\n");
    else if (centered) {
        rend->render_mode_x = RENDER_MODE_CENTERED;
        if (rend->type != GC_TXTREND)
            rend->render_mode_y = RENDER_MODE_CENTERED;
    }
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct fixed_to_cam *cmp = (struct fixed_to_cam *)component;
    struct renderer *rend = GETCMP(entity, renderer);
    char *tmp;

    cmp->pos.x = xml_getintprop(n, "x");
    cmp->pos.y = xml_getintprop(n, "y");
    tmp = xml_gettempprop(n, "x");
    cmp->per_x = tmp && my_strchr(tmp, '%');
    tmp = xml_gettempprop(n, "y");
    cmp->per_y = tmp && my_strchr(tmp, '%');
    cmp->size_x = xml_getintprop(n, "width");
    tmp = xml_gettempprop(n, "width");
    cmp->per_w = tmp && my_strchr(tmp, '%');
    cmp->size_y = xml_getintprop(n, "height");
    tmp = xml_gettempprop(n, "height");
    cmp->per_h = tmp && my_strchr(tmp, '%');
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