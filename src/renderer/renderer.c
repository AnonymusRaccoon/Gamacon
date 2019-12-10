/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** render
*/

#include "engine.h"
#include "sprite.h"
#include <SFML/Graphics.h>

void renderer_draw_texture(gc_engine *engine, gc_sprite *sprite)
{
    sfVector2f pos = (sfVector2f){sprite->pos.x, sprite->pos.y};
    sfVector2f scale;
    sfVector2u t;
    sfIntRect rect = {
        (int)sprite->rect.left, (int)sprite->rect.top,
        (int)sprite->rect.width, (int)sprite->rect.height
    };

    if (!sprite->texture)
        return;
    t = sfTexture_getSize(sprite->texture->texture);
    scale = (sfVector2f){sprite->size.x / t.x, sprite->size.y / t.y};
    sfSprite_setTexture(engine->sprite, sprite->texture->texture, true);
    sfSprite_setPosition(engine->sprite, pos);
    sfSprite_setScale(engine->sprite, scale);
    sfSprite_setTextureRect(engine->sprite, rect);
    sfRenderWindow_drawSprite(engine->window, engine->sprite, NULL);
}

void renderer_draw(gc_engine *engine)
{
    sfRenderWindow_display(engine->window);
    sfRenderWindow_clear(engine->window, sfBlack);
}