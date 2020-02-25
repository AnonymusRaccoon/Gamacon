/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "sprite.h"
#include "systems/sfml_renderer_system.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "components/vertex_component.h"
#include "my.h"
#include "sfml_renderer.h"
#include "text.h"
#include <stdlib.h>

gc_vector2 sfml_get_text_size(sf_renderer *this, gc_text *text)
{
	sfFloatRect bounds;

	sfText_setString(this->text, text->text);
	sfText_setFont(this->text, text->font);
	bounds = sfText_getLocalBounds(this->text);
	return (gc_vector2) {bounds.width, bounds.height};
}

void sfml_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dt)
{
    struct transform_component *pos = GETCMP(entity, transform_component);
    struct renderer *text = GETCMP(entity, renderer);
    struct sfml_renderer_system *rend = (struct sfml_renderer_system *)system;

    if (!text->data)
        return;
    switch (text->type) {
    case GC_TEXTUREREND:
        sfmlrenderer_draw_texture(rend, pos, entity, (gc_sprite *)text->data);
        break;
    case GC_ANIMREND:
        sfmlrenderer_draw_anim(rend, entity, (gc_animholder *)text->data, dt);
        break;
    case GC_TXTREND:
        sfmlrenderer_draw_txt(rend, pos, (gc_text *)text->data);
        break;
    case GC_MAP:
        sfmlrenderer_draw_tilemap(rend, (struct vertex_component *)text->data);
        break;
    default:
        my_printf("Trying to render a texture with an unknown type.\n");
        break;
    }
    (void)engine;
}

void sfml_setup_options(gc_engine *engine)
{
    engine->is_open = &sfml_is_open;
    engine->has_focus = &sfml_has_focus;
    engine->is_keypressed = &sfml_is_keypressed;
    engine->handle_events = &sfml_handle_events;
    engine->draw = &sfml_draw;
    engine->play_music = &sfml_play_music;
    engine->stop_music = &sfml_stop_music;
}

void sfmlrend_ctr(void *rend, va_list list)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)rend;
    sfVideoMode mode = {800, 600, 32};
    gc_engine *engine = va_arg(list, gc_engine *);
    const char *title = va_arg(list, const char *);
    int framerate = va_arg(list, int);

    renderer->get_text_size = &sfml_get_text_size;
    renderer->window = sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);
    renderer->sprite = sfSprite_create();
    renderer->view = sfView_create();
    renderer->text = sfText_create();
    renderer->vertices = sfml_init_verticies();
    if (!renderer->window || !renderer->sprite || \
!renderer->view || !renderer->text || !renderer->vertices)
        return;
    sfRenderWindow_setFramerateLimit(renderer->window, framerate);
    sfView_setSize(renderer->view, (sfVector2f){800, 600});
    sfView_setCenter(renderer->view, (sfVector2f){400, -300});
    sfRenderWindow_setView(renderer->window, renderer->view);
    sfml_setup_options(engine);
}

void sfmlrend_dtr(void *system)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
system;

    sfRenderWindow_destroy(renderer->window);
    sfSprite_destroy(renderer->sprite);
    sfText_destroy(renderer->text);
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