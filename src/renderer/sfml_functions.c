/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** sfml_functions
*/

#include "engine.h"
#include <SFML/Graphics.h>
#include "systems/sfml_renderer_system.h"

bool sfml_is_open(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
engine->get_system(engine, "SfmlrendererSystem");

    return (sfRenderWindow_isOpen(renderer->window));
}

bool sfml_has_focus(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
engine->get_system(engine, "SfmlrendererSystem");

    return (sfRenderWindow_hasFocus(renderer->window));
}

bool sfml_is_keypressed(int key)
{
    return (sfKeyboard_isKeyPressed(key));
}

void sfml_handle_events(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
engine->get_system(engine, "SfmlrendererSystem");
    sfEvent event;

    while (sfRenderWindow_pollEvent(renderer->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(renderer->window);
    }
}

void sfml_draw(gc_engine *engine)
{
    struct sfml_renderer_system *renderer = (struct sfml_renderer_system *)\
engine->get_system(engine, "SfmlrendererSystem");

    sfRenderWindow_display(renderer->window);
    sfRenderWindow_clear(renderer->window, sfBlack);
}