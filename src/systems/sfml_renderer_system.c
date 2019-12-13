/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "systems/sfml_renderer_system.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include <stdlib.h>

void renderer_draw_texture(struct sfml_renderer_system *renderer, \
gc_sprite *sprite)
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
    sfSprite_setTexture(renderer->sprite, sprite->texture->texture, true);
    sfSprite_setPosition(renderer->sprite, pos);
    sfSprite_setScale(renderer->sprite, scale);
    sfSprite_setTextureRect(renderer->sprite, rect);
    sfRenderWindow_drawSprite(renderer->window, renderer->sprite, NULL);
}

void sfml_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    struct renderer *text = (struct renderer *)\
entity->get_component(entity, "Renderer");
    struct sfml_renderer_system *rend = (struct sfml_renderer_system *)system;

    if (!text->sprite)
        return;
    text->sprite->pos = pos->position;
    text->sprite->size = pos->size;
    if (text->type == GC_TEXTUREREND)
        renderer_draw_texture(rend, text->sprite);
    (void)dtime;
    (void)engine;
}

void sfmlrend_ctr(void *rend, va_list list)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)rend;
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;
    gc_engine *engine = va_arg(list, gc_engine *);
    const char *title = va_arg(list, const char *);
    int framerate = va_arg(list, int);

    renderer->window = sfRenderWindow_create(mode, title, style, NULL);
    renderer->sprite = sfSprite_create();
    if (!renderer->window || !renderer->sprite)
        return;
    sfRenderWindow_setFramerateLimit(renderer->window, framerate);
    engine->is_open = &sfml_is_open;
    engine->has_focus = &sfml_has_focus;
    engine->is_keypressed = &sfml_is_keypressed;
    engine->handle_events = &sfml_handle_events;
    engine->draw = &sfml_draw;
}

void sfmlrend_dtr(void *system)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
system;

    sfRenderWindow_destroy(renderer->window);
    sfSprite_destroy(renderer->sprite);
}

const struct sfml_renderer_system sfml_renderer = {
    {
        name: "SfmlRendererSystem",
        component_name: "Renderer",
        size: sizeof(struct sfml_renderer_system),
        ctr: &sfmlrend_ctr,
        dtr: &sfmlrend_dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &sfml_update_entity,
        destroy: &system_destroy
    },
    window: NULL,
    sprite: NULL
};