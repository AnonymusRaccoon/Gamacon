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
#include "sprite.h"
#include "systems/sfml_renderer_system.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "my.h"
#include <stdlib.h>

void renderer_draw_texture(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_sprite *sprite)
{
    sfVector2f pos = (sfVector2f){tra->position.x, -tra->position.y};
    sfVector2f scale = (sfVector2f){
        tra->size.x * sprite->scale.x / sprite->rect.width,
        tra->size.y * sprite->scale.y / sprite->rect.height
    };;

    sprite->pos = tra->position;
    if (!sprite->texture)
        return;
    sfSprite_setTexture(renderer->sprite, sprite->texture->texture, true);
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

void renderer_draw_anim(struct sfml_renderer_system *renderer, \
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
    renderer_draw_texture(renderer, tra, holder->sprite);
}

void sfml_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct transform_component *pos = GETCMP(transform_component);
    struct renderer *text = GETCMP(renderer);
    struct sfml_renderer_system *rend = (struct sfml_renderer_system *)system;

    if (!text->data)
        return;
    switch (text->type) {
    case GC_TEXTUREREND:
        renderer_draw_texture(rend, pos, (gc_sprite *)text->data);
        break;
    case GC_ANIMREND:
        renderer_draw_anim(rend, pos, (gc_animholder *)text->data, dtime);
        break;
    default:
        my_printf("Trying to render a texture with an unknown type.\n");
        break;
    }
    (void)dtime;
    (void)engine;
}

void sfmlrend_ctr(void *rend, va_list list)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)rend;
    sfVideoMode mode = {800, 600, 32};
    gc_engine *engine = va_arg(list, gc_engine *);
    const char *title = va_arg(list, const char *);
    int framerate = va_arg(list, int);

    renderer->window = sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);
    renderer->sprite = sfSprite_create();
    renderer->view = sfView_create();
    if (!renderer->window || !renderer->sprite || !renderer->view)
        return;
    sfRenderWindow_setFramerateLimit(renderer->window, framerate);
    sfView_setSize(renderer->view, (sfVector2f){800, 600});
    sfView_setCenter(renderer->view, (sfVector2f){400, -300});
    sfRenderWindow_setView(renderer->window, renderer->view);
    engine->is_open = &sfml_is_open;
    engine->has_focus = &sfml_has_focus;
    engine->is_keypressed = &sfml_is_keypressed;
    engine->handle_events = &sfml_handle_events;
    engine->draw = &sfml_draw;
    engine->play_music = &sfml_play_music;
}

void sfmlrend_dtr(void *system)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
system;

    sfRenderWindow_destroy(renderer->window);
    sfSprite_destroy(renderer->sprite);
    sfView_destroy(renderer->view);
}

const struct sfml_renderer_system sfml_renderer = {
    {
        name: "sfml_renderer_system",
        component_name: "renderer",
        size: sizeof(struct sfml_renderer_system),
        ctr: &sfmlrend_ctr,
        dtr: &sfmlrend_dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &sfml_update_entity,
        destroy: &system_destroy
    },
    window: NULL,
    sprite: NULL,
    view: NULL
};