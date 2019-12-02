/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** event_handler
*/

#include "engine.h"

void handle_events(gc_engine *engine)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(engine->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(engine->window);
    }
}