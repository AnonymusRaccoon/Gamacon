/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#include "engine.h"
#include "xml.h"
#include "utility.h"
#include "components/transform_component.h"
#include "components/texture_renderer.h"
#include <stdlib.h>

static void texture_rend_ctr(void *component, va_list args)
{
    struct texture_renderer *cmp = (struct texture_renderer *)component;
    sfVector2u size;

    cmp->sprite = malloc(sizeof(gc_sprite));
    if (!cmp->sprite)
        return;
    cmp->sprite->texture = va_arg(args, gc_texture *);
    cmp->sprite->rect = va_arg(args, gc_int_rect);
    if (cmp->sprite->texture && cmp->sprite->rect.height < 0) {
        size = sfTexture_getSize(cmp->sprite->texture->texture);
        cmp->sprite->rect.height = (float)size.y;
        cmp->sprite->rect.width = (float)size.x;
    }
}

static void texture_rend_fdctr(gc_engine *engine, void *component, node *n)
{
    struct texture_renderer *cmp = (struct texture_renderer *)component;
    node *rect = xml_getnode(n, "Rect");
    sfVector2u size;

    cmp->sprite = malloc(sizeof(gc_sprite));
    if (!cmp->sprite)
        return;
    cmp->sprite->texture = get_texture(engine, xml_getproperty(n, "src"));
    cmp->sprite->rect.height = xml_getfloatprop(rect, "height");
    cmp->sprite->rect.width = xml_getfloatprop(rect, "width");
    cmp->sprite->rect.top = xml_getfloatprop(rect, "top");
    cmp->sprite->rect.left = xml_getfloatprop(rect, "left");
    if (cmp->sprite && cmp->sprite->rect.height < 0) {
        size = sfTexture_getSize(cmp->sprite->texture->texture);
        cmp->sprite->rect.height = (float)size.y;
        cmp->sprite->rect.width = (float)size.x;
    }
}

static void texture_rend_dtr(void *component)
{
    (void)component;
}

static char *texture_rend_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct texture_renderer texture_renderer = {
    base: {
        name: "TextureRenderer",
        size: sizeof(struct texture_renderer),
        dependencies: (char *[]){"TransformComponent", NULL},
        ctr: &texture_rend_ctr,
        fdctr: &texture_rend_fdctr,
        dtr: &texture_rend_dtr,
        serialize: &texture_rend_serialize,
        destroy: &component_destroy,
        next: NULL,
        prev: NULL
    },
    sprite: NULL,
};