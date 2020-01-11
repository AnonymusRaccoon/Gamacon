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
    GC_TEXTURETYPE type = va_arg(args, GC_TEXTURETYPE);

    cmp->data = NULL;
    if (type == GC_TEXTUREREND)
        sprite_ctr(cmp, args);
    if (type == GC_ANIMREND)
        anim_ctr(cmp, args);
    if (type == GC_TXTREND)
        text_ctr(cmp, args);
}

GC_TEXTURETYPE renderer_get_type(node *n)
{
    if (xml_getnode(n, "animation"))
        return (GC_ANIMREND);
    if (xml_hasproperty(n, "text"))
        return (GC_TXTREND);
    return (GC_TEXTUREREND);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct renderer *cmp = (struct renderer *)component;
    GC_TEXTURETYPE type = renderer_get_type(n);

    if (type == GC_TEXTUREREND)
        sprite_fdctr(scene, cmp, n);
    if (type == GC_ANIMREND)
        anim_fdctr(scene, cmp, n);
    if (type == GC_TXTREND)
        text_fdctr(scene, cmp, n);
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
        break;
    case GC_TXTREND:
        free(((gc_text *)cmp->data)->text);
        break;
    default:
        break;
    }
    free(cmp->data);
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