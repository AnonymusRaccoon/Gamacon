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
    sfml_renderer_system *renderer = (sfml_renderer_system *)\
engine->get_system(engine, "SfmlRendererSystem");

    return (sfRenderWindow_isOpen(renderer->window));
}

void sfml_handle_events(gc_engine *engine)
{
    sfml_renderer_system *renderer = (sfml_renderer_system *)\
engine->get_system(engine, "SfmlRendererSystem");
    sfEvent event;

    while (sfRenderWindow_pollEvent(renderer->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(renderer->window);
    }
}

void sfml_draw(gc_engine *engine)
{
    sfml_renderer_system *renderer = (sfml_renderer_system *)\
engine->get_system(engine, "SfmlRendererSystem");

    sfRenderWindow_display(renderer->window);
    sfRenderWindow_clear(renderer->window, sfBlack);
}