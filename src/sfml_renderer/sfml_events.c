/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** sfml_events
*/

#include "engine.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "sfml_renderer.h"
#include "systems/sfml_renderer_system.h"

void sfml_handle_event(gc_engine *eng, sfEvent e)
{
    switch (e.type) {
        case sfEvtResized:
            eng->on_resize(eng, (gc_vector2){e.size.width, e.size.height});
            break;
        case sfEvtMouseButtonReleased:
            if (e.mouseButton.button == sfMouseLeft)
                eng->trigger_event(eng, "mouse_click", GC_LEFT);
            if (e.mouseButton.button == sfMouseRight)
                eng->trigger_event(eng, "mouse_click", GC_RIGHT);
            break;
        case sfEvtKeyReleased:
            eng->trigger_event(eng, "key_pressed", e.key.code);
            break;
        default:
            break;
    }
}

void sfml_handle_events(gc_engine *eng)
{
    struct sfml_renderer_system *rend = GETSYS(eng, sfml_renderer_system);
    sfEvent e;

    while (sfRenderWindow_pollEvent(rend->window, &e)) {
        if (e.type == sfEvtClosed) {
            sfRenderWindow_close(rend->window);
            continue;
        }
        sfml_handle_event(eng, e);
    }
}

gc_vector2 sfml_engine_get_cursor_pos(gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    sfVector2i pos;
    gc_vector2 ret;
    sfVector2f pos2;

    pos = sfMouse_getPositionRenderWindow(rend->window);
    pos2 = sfRenderWindow_mapPixelToCoords(rend->window, pos, rend->view);
    ret.x = pos2.x;
    ret.y = pos2.y;
    ret.y *= -1;
    return (ret);
}

void sfml_resize(gc_engine *engine, gc_vector2 size)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    sfView_setSize(rend->view, (sfVector2f){
        size.x,
        size.y
    });
    entities_update_to_cam_size(engine->scene, size);
}

gc_vector2 sfml_get_screen_size(gc_engine *engine)
{
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
    sfVector2u size = sfRenderWindow_getSize(rend->window);

    return (gc_vector2){size.x, size.y};
}