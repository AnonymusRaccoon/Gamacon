/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_drawer
*/

#include "sfml_renderer.h"
#include "vector2.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include <SFML/Graphics.h>

void sfmlrenderer_draw_texture(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_sprite *sprite)
{
    sfVector2f pos = (sfVector2f){tra->position.x, -tra->position.y};
    sfVector2f scale = (sfVector2f){
        tra->size.x * sprite->scale.x / sprite->rect.width,
        tra->size.y * sprite->scale.y / sprite->rect.height
    };

    sprite->pos = tra->position;
    if (!sprite->texture)
        return;
    sfSprite_setTexture(renderer->sprite, sprite->texture, true);
    sfSprite_setTextureRect(renderer->sprite, (sfIntRect){
        (int)sprite->rect.left, (int)sprite->rect.top,
        (int)sprite->rect.width, (int)sprite->rect.height
    });
    sfSprite_setPosition(renderer->sprite, pos);
    sfSprite_setScale(renderer->sprite, scale);
    sfSprite_setOrigin(renderer->sprite, (sfVector2f){
        scale.x < 0 ? sprite->rect.width : 0,
        scale.y < 0 ? sprite->rect.height : 0
    });
    sfRenderWindow_drawSprite(renderer->window, renderer->sprite, NULL);
}

void sfmlrenderer_draw_anim(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_animholder *holder, float dtime)
{
    gc_int_rect *rec = &holder->sprite->rect;
    gc_anim *curr = holder->current;

    if (curr)
        holder->timesince_up += dtime;
    if (curr && holder->timesince_up > 1 / curr->frame_rate) {
        rec->left += rec->width;
        holder->timesince_up = 0;
        if (rec->left > curr->rect.left + rec->width * (curr->frame_count - 1))
            rec->left = curr->rect.left;
    }
    sfmlrenderer_draw_texture(renderer, tra, holder->sprite);
}

void sfmlrenderer_draw_txt(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_text *txt)
{
    sfText_setString(renderer->text, txt->text);
    sfText_setFont(renderer->text, txt->font);
    sfText_setPosition(renderer->text, (sfVector2f){
        tra->position.x,
        -tra->position.y
    });
    sfRenderWindow_drawText(renderer->window, renderer->text, NULL);
}