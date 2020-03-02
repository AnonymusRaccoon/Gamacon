/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** sfml_functions
*/

#include "engine.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "sfml_renderer.h"
#include "systems/sfml_renderer_system.h"
#include "systems/camerafollow_system.h"
#include "components/transform_component.h"

bool sfml_is_open(gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    if (engine->should_close)
        return (false);
    return (sfRenderWindow_isOpen(rend->window));
}

bool sfml_has_focus(gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    return (sfRenderWindow_hasFocus(rend->window));
}

bool sfml_is_keypressed(int key)
{
    return (sfKeyboard_isKeyPressed(key));
}

void sfml_draw(gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    struct camerafollow_system *cam = GETSYS(engine, camerafollow_system);

    if (cam) {
        sfView_setCenter(rend->view, (sfVector2f){
            cam->cam_pos.x,
            -cam->cam_pos.y
        });
        sfRenderWindow_setView(rend->window, rend->view);
        entities_update_to_cam(engine->scene, rend, cam);
    }
    sfRenderWindow_display(rend->window);
    sfRenderWindow_clear(rend->window, sfBlack);
}