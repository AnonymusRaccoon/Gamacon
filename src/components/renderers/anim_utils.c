/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** anim_utils.c
*/

#include "sprite.h"
#include "my.h"
#include "renderer.h"

void rend_set_anim(struct renderer *rend, const char *name)
{
    gc_animholder *holder = (gc_animholder *)rend->data;

    if (holder->current && !my_strcmp(holder->current->name, name))
        return;
    for (int i = 0; i < holder->animcount; i++) {
        if (!my_strcmp(holder->anims[i].name, name)) {
            holder->current = &holder->anims[i];
            holder->sprite->rect = holder->anims[i].rect;
            return;
        }
    }
    my_printf("Gamacon: unknown animation %s.\n", name);
}