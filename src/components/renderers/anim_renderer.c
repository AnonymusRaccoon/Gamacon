/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** anim_renderer
*/

#include "components/renderer.h"
#include "vector2.h"
#include "sprite.h"
#include "xml.h"
#include "my.h"
#include <malloc.h>

void destroy_anim_renderer(struct renderer *cmp)
{
    for (int i = 0; i < ((gc_animholder *)cmp->data)->animcount; i++) {
        if (my_strcmp(((gc_animholder *)cmp->data)->anims[i].name, "none"))
            free(((gc_animholder *)cmp->data)->anims[i].name);
    }
    free(((gc_animholder *)cmp->data)->sprite);
    free(((gc_animholder *)cmp->data)->anims);
    free(cmp->data);
}

void anim_ctr(struct renderer *cmp, va_list args)
{
    sfVector2u size;
    gc_sprite *sprite = malloc(sizeof(gc_sprite));

    if (!sprite)
        return;
    cmp->data = sprite;
    cmp->destroy = &destroy_anim_renderer;
    sprite->texture = va_arg(args, sfTexture *);
    sprite->rect = va_arg(args, gc_int_rect);
    if (sprite->texture && sprite->rect.height < 0) {
        size = sfTexture_getSize(sprite->texture);
        sprite->rect.height = (float)size.y;
        sprite->rect.width = (float)size.x;
    }
}

void animation_fdctr(gc_anim *anim, gc_sprite *sprite, node *n)
{
    node *rect = xml_getnode(n, "Rect");
    int tmp;

    anim->name = xml_getproperty(n, "name");
    anim->frame_count = xml_getintprop(n, "frame_count");
    anim->frame_rate = xml_getfloatprop(n, "frame_rate");
    anim->rect.height = sprite->rect.height;
    anim->rect.width = sprite->rect.width;
    anim->rect.top = sprite->rect.top;
    anim->rect.left = sprite->rect.left;
    if ((tmp = xml_getintprop(rect, "height")) != 0)
        anim->rect.height = tmp;
    if ((tmp = xml_getintprop(rect, "width")) != 0)
        anim->rect.width = tmp;
    if ((tmp = xml_getintprop(rect, "top")) != 0)
        anim->rect.top = tmp;
    if ((tmp = xml_getintprop(rect, "left")) != 0)
        anim->rect.left = tmp;
}

void animation_setnone(gc_anim *anim, gc_sprite *sprite)
{
    anim->name = "none";
    anim->frame_count = 1;
    anim->frame_rate = 0;
    anim->rect = sprite->rect;
}

void anim_fdctr(gc_scene *scene, struct renderer *cmp, node *n)
{
    gc_animholder *hold = malloc(sizeof(gc_animholder));
    int animcount = xml_getchildcount_filtered(n, "animation") + 1;
    int i = 1;

    if (!hold || !(hold->anims = malloc(sizeof(gc_anim) * animcount)))
        return;
    sprite_fdctr(scene, cmp, n);
    hold->sprite = (gc_sprite *)cmp->data;
    hold->current = NULL;
    hold->animcount = animcount;
    hold->timesince_up = 0;
    cmp->data = hold;
    cmp->destroy = &destroy_anim_renderer;
    animation_setnone(&hold->anims[0], hold->sprite);
    for (n = n->child; n; n = n->next) {
        if (my_strcmp(n->name, "animation"))
            continue;
        animation_fdctr(&hold->anims[i], hold->sprite, n);
        i++;
    }
}