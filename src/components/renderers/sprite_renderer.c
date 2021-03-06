/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sprite_renderer
*/

#include "components/renderer.h"
#include "vector2.h"
#include "xml.h"
#include "sprite.h"
#include "sfml_renderer.h"
#include <malloc.h>
#include <SFML/Graphics.h>

void destroy_sprite(struct renderer *cmp)
{
    free(cmp->data);
}

void sprite_ctr(struct renderer *cmp, va_list args)
{
    sfVector2u size;
    gc_sprite *sprite;

    sprite = malloc(sizeof(gc_sprite));
    if (!sprite)
        return;
    cmp->data = sprite;
    cmp->destroy = &destroy_sprite;
    sprite->texture = va_arg(args, sfTexture *);
    sprite->rect = va_arg(args, gc_int_rect);
    if (sprite->texture && sprite->rect.height <= 0) {
        size = sfTexture_getSize(sprite->texture);
        sprite->rect.height = (int)size.y;
        sprite->rect.width = (int)size.x;
    }
    sprite->scale = (gc_vector2){1, 1};
}

void sprite_fdctr(gc_scene *scene, struct renderer *cmp, node *n)
{
    node *rect = xml_getnode(n, "Rect");
    sfVector2u size;
    gc_sprite *sprite = malloc(sizeof(gc_sprite));

    if (!sprite)
        return;
    cmp->data = sprite;
    cmp->destroy = &destroy_sprite;
    sprite->texture = get_texture(scene, xml_gettempprop(n, "src"));
    sprite->rect.height = xml_getintprop(rect, "height");
    sprite->rect.width = xml_getintprop(rect, "width");
    sprite->rect.top = xml_getintprop(rect, "top");
    sprite->rect.left = xml_getintprop(rect, "left");
    if (sprite->texture && sprite->rect.height <= 0) {
        size = sfTexture_getSize(sprite->texture);
        sprite->rect.height = (int)size.y;
        sprite->rect.width = (int)size.x;
    }
    sprite->scale = (gc_vector2){1, 1};
}
