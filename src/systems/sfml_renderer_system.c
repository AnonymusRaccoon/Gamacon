/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "systems/sfml_renderer_system.h"
#include "components/renderer.h"
#include "my.h"
#include "sfml_renderer.h"
#include "text.h"

gc_vector2 sfml_get_text_size(sf_renderer *this, gc_text *text)
{
    sfFloatRect bounds;

    sfText_setString(this->text, text->text);
    sfText_setFont(this->text, text->font);
    bounds = sfText_getLocalBounds(this->text);
    return (gc_vector2) {bounds.width * 1.3, bounds.height * 2.5};
}

static drawer drawers[] = {
    (drawer)&sfmlrenderer_draw_texture,
    (drawer)&sfmlrenderer_draw_anim,
    (drawer)&sfmlrenderer_draw_txt,
    (drawer)&sfmlrenderer_draw_tilemap,
    NULL
};

void sfml_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dt)
{
    struct renderer *text = GETCMP(entity, renderer);

    if (!text->data || !text->is_visible)
        return;
    if (text->type > 3) {
        my_printf("Trying to render a texture with an unknown type.\n");
        return;
    }
    drawers[text->type](engine, entity, text->data, dt);
}

void sfml_setup_options(struct sfml_renderer_system *this, gc_engine *engine)
{
    this->is_fullscreen = false;
    this->resolution = (gc_vector2i){800, 600};
    engine->is_open = &sfml_is_open;
    engine->has_focus = &sfml_has_focus;
    engine->is_keypressed = &sfml_is_keypressed;
    engine->handle_events = &sfml_handle_events;
    engine->draw = &sfml_draw;
    engine->play_music = &sfml_play_music;
    engine->stop_music = &sfml_stop_music;
    engine->on_resize = &sfml_resize;
    engine->get_screen_size = &sfml_get_screen_size;
    engine->get_cursor_pos = &sfml_engine_get_cursor_pos;
}

void sfmlrend_ctr(void *rend, va_list list)
{
    struct sfml_renderer_system *this = (struct sfml_renderer_system *)rend;
    sfVideoMode mode = {800, 600, 32};
    gc_engine *engine = va_arg(list, gc_engine *);
    const char *title = va_arg(list, const char *);
    this->framerate = va_arg(list, int);

    this->get_text_size = &sfml_get_text_size;
    this->window = sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);
    this->sprite = sfSprite_create();
    this->view = sfView_create();
    this->text = sfText_create();
    this->vertices = sfml_init_verticies();
    this->states = sfml_init_render_state();
    if (!this->window || !this->sprite || \
!this->view || !this->text || !this->vertices || !this->states)
        return;
    sfRenderWindow_setFramerateLimit(this->window, this->framerate);
    sfView_setSize(this->view, (sfVector2f){800, 600});
    sfView_setCenter(this->view, (sfVector2f){400, -300});
    sfRenderWindow_setView(this->window, this->view);
    sfml_setup_options(this, engine);
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