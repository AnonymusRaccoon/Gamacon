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

void renderer_draw_texture(sfml_renderer_system *renderer, gc_sprite *sprite)
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

void sfml_update_entity(void *system, gc_entity *entity, float dtime)
{
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    struct renderer *text = (struct renderer *)\
entity->get_component(entity, "Renderer");

    if (!text->sprite)
        return;
    text->sprite->pos = pos->position;
    text->sprite->size = pos->size;
    if (text->type == GC_TEXTUREREND)
        renderer_draw_texture((sfml_renderer_system *)system, text->sprite);
    (void)dtime;
}

void sfml_destroy(void *system)
{
    sfml_renderer_system *renderer = (sfml_renderer_system *)system;

    sfRenderWindow_destroy(renderer->window);
    sfSprite_destroy(renderer->sprite);
}

const sfml_renderer_system sfml_renderer = {
    {
        name: "SfmlRendererSystem",
        component_name: "Renderer",
        check_dependencies: &system_check_dependencies,
        update_entity: &sfml_update_entity,
        destroy: &sfml_destroy
    },
    window: NULL,
    sprite: NULL
};

gc_system *gc_new_sfml_renderer(gc_engine *engine, \
const char *title, int framerate)
{
    sfml_renderer_system *renderer = malloc(sizeof(sfml_renderer_system));
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;

    if (!renderer)
        return (NULL);
    *renderer = sfml_renderer;
    renderer->window = sfRenderWindow_create(mode, title, style, NULL);
    renderer->sprite = sfSprite_create();
    if (!renderer->window || !renderer->sprite)
        return (NULL);
    sfRenderWindow_setFramerateLimit(renderer->window, framerate);
    engine->is_open = &sfml_is_open;
    engine->handle_events = &sfml_handle_events;
    engine->draw = &sfml_draw;
    return ((gc_system *)renderer);
}