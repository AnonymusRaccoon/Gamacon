/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** render
*/

#include "engine.h"
#include <SFML/Graphics.h>


void renderer_draw_texture(gc_engine *engine, gc_texture *text, \
gc_vector2 pos, gc_vector2 scale)
{
    if (!text)
        return;
    sfSprite_setTexture(engine->sprite, text->texture, true);
    sfSprite_setPosition(engine->sprite, (sfVector2f){pos.x, pos.y});
    sfSprite_setScale(engine->sprite, (sfVector2f){scale.x, scale.y});
    sfRenderWindow_drawSprite(engine->window, engine->sprite, NULL);
}

void renderer_draw(gc_engine *engine)
{
    sfRenderWindow_display(engine->window);
    sfRenderWindow_clear(engine->window, sfBlack);
}