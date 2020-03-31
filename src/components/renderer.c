/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#include "engine.h"
#include "xml.h"
#include "components/renderer.h"
#include <stdbool.h>
#include <stddef.h>

static void ctr(void *component, va_list args)
{
    struct renderer *cmp = (struct renderer *)component;
    gc_texturetype type = va_arg(args, gc_texturetype);

    cmp->destroy = NULL;
    cmp->data = NULL;
    cmp->type = type;
    cmp->is_visible = true;
    cmp->is_centered_x = false;
    cmp->is_centered_y = false;
    if (type == GC_TEXTUREREND)
        sprite_ctr(cmp, args);
    if (type == GC_ANIMREND)
        anim_ctr(cmp, args);
    if (type == GC_TXTREND)
        text_ctr(cmp, args);
    if (type == GC_MAP)
        map_ctr(cmp, args);
}

gc_texturetype renderer_get_type(node *n)
{
    if (xml_getnode(n, "animation"))
        return (GC_ANIMREND);
    if (xml_hasproperty(n, "text"))
        return (GC_TXTREND);
    if (xml_hasproperty(n, "vertex"))
        return (GC_MAP);
    return (GC_TEXTUREREND);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct renderer *cmp = (struct renderer *)component;
    gc_texturetype type = renderer_get_type(n);

    cmp->destroy = NULL;
    cmp->type = type;
    cmp->is_visible = true;
    if (type == GC_TEXTUREREND)
        sprite_fdctr(scene, cmp, n);
    if (type == GC_ANIMREND)
        anim_fdctr(scene, cmp, n);
    if (type == GC_TXTREND)
        text_fdctr(scene, cmp, n);
    if (type == GC_MAP)
        map_fdctr(scene, cmp, entity);
    (void)entity;
}

static void dtr(void *component)
{
    struct renderer *cmp = (struct renderer *)component;

    if (cmp->destroy)
        cmp->destroy(cmp);
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct renderer renderer_component = {
    base: {
        name: "renderer",
        size: sizeof(struct renderer),
        dependencies: (char *[]){"transform_component", NULL},
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy,
        next: NULL,
        prev: NULL
    },
    data: NULL,
    type: GC_TEXTUREREND
};