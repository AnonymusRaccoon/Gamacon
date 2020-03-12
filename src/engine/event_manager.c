/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** scene_event
*/

#include <stdbool.h>
#include "my.h"
#include "scene.h"
#include "engine.h"
#include "malloc.h"
#include "event_manager.h"

bool engine_add_event_listener(gc_engine *engine, const char *name, \
void (*func)(gc_engine *, va_list))
{
    struct gc_event_listener *node = malloc(sizeof(struct gc_event_listener));
    char *n_name = my_strdup(name);

    if (!name || !node || !n_name)
        return (false);
    node->name = n_name;
    node->func = func;
    LISTADD(engine->event_listeners, node);
    return (true);
}

void engine_trigger_event(gc_engine *engine, const char *name, ...)
{
    gc_list *tmp = engine->event_listeners;
    va_list list;

    while (tmp) {
        if (!my_strcmp(((struct gc_event_listener *)tmp->data)->name, name)) {
            va_start(list, name);
            ((struct gc_event_listener *) tmp->data)->func(engine, list);
            va_end(list);
        }
        tmp = tmp->next;
    }
}

void engine_setup_event(gc_engine *engine)
{
    engine->on_resize = &engine_on_resize;
    engine->event_listeners = NULL;
    engine->add_event_listener = &engine_add_event_listener;
    engine->trigger_event = &engine_trigger_event;
}