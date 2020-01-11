/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** sfml_functions
*/

#include "engine.h"
#include <SFML/Graphics.h>
#include "sfml_renderer.h"
#include "systems/sfml_renderer_system.h"
#include "systems/camerafollow_system.h"
#include "components/transform_component.h"

bool sfml_is_open(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);

    if (engine->should_close)
        return (false);
    return (sfRenderWindow_isOpen(renderer->window));
}

bool sfml_has_focus(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);

    return (sfRenderWindow_hasFocus(renderer->window));
}

bool sfml_is_keypressed(int key)
{
    return (sfKeyboard_isKeyPressed(key));
}

void sfml_handle_events(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);
    sfEvent event;

    while (sfRenderWindow_pollEvent(renderer->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(renderer->window);
        if (event.type == sfEvtResized) {
            sfView_setSize(renderer->view, (sfVector2f){
                event.size.width,
                event.size.height
            });
            entities_update_to_cam_size(engine->scene, (gc_vector2) {
                event.size.width,
                event.size.height
            });
        }
    }
}

void sfml_draw(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);
    struct camerafollow_system *cam = GETSYS(camerafollow_system);

    if (cam) {
        sfView_setCenter(renderer->view, (sfVector2f){
            cam->cam_pos.x,
            -cam->cam_pos.y
        });
        sfRenderWindow_setView(renderer->window, renderer->view);
        entities_update_to_cam(engine->scene, renderer, cam);
    }
    sfRenderWindow_display(renderer->window);
    sfRenderWindow_clear(renderer->window, sfBlack);
}