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
    struct gc_event_listener *n = malloc(sizeof(struct gc_event_listener));
    char *n_name = my_strdup(name);

    if (!name || !n || !n_name)
        return (false);
    n->name = n_name;
    n->func = func;
    LISTADD(engine->event_listeners, n);
    return (true);
}

bool engine_remove_event_listener(gc_engine *engine, const char *n, \
void (*func)(gc_engine *, va_list))
{
    gc_list *tmp = engine->event_listeners;

    for (; tmp; tmp = tmp->next) {
        if (((struct gc_event_listener *)tmp->data)->func != func)
            continue;
        if (n && my_strcmp(((struct gc_event_listener *)tmp->data)->name, n))
            continue;
        LISTREM(engine->event_listeners, tmp);
        return (true);
    }
    return (false);
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
    engine->remove_event_listener = &engine_remove_event_listener;
    engine->trigger_event = &engine_trigger_event;
}

int change_scene(gc_engine *engine, gc_scene *scene)
{
    void *music = scene->get_data(scene, "music", NULL);

    engine->stop_music(engine);
    if (engine->scene)
        engine->scene->destroy(engine->scene);
    engine->scene = scene;
    if (music)
        engine->play_music(music);
    engine->on_resize(engine, engine->get_screen_size(engine));
    return (0);
}