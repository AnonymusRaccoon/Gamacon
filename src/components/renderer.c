/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#include "engine.h"
#include "xml.h"
#include "utility.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include <stdlib.h>

static void ctr(void *component, va_list args)
{
    struct renderer *cmp = (struct renderer *)component;
    gc_texturetype type = va_arg(args, gc_texturetype);

    cmp->data = NULL;
    cmp->type = type;
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

    cmp->type = type;
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

    switch (cmp->type) {
    case GC_ANIMREND:
        for (int i = 0; i < ((gc_animholder *)cmp->data)->animcount; i++) {
            if (my_strcmp(((gc_animholder *)cmp->data)->anims[i].name, "none"))
                free(((gc_animholder *)cmp->data)->anims[i].name);
        }
        free(((gc_animholder *)cmp->data)->sprite);
        free(((gc_animholder *)cmp->data)->anims);
        free(cmp->data);
        break;
    case GC_TXTREND:
        free(((gc_text *)cmp->data)->text);
        free(cmp->data);
        break;
    case GC_TEXTUREREND:
        free(cmp->data);
        break;
    default:
        break;
    }
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