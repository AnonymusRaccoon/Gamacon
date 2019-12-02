/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/
typedef struct gc_engine gc_engine;

#pragma once

#include "scene.h"
#include <stdbool.h>

 struct gc_engine
{
    gc_scene *scene;
    bool (*is_open)(struct gc_engine *engine);
    int (*game_loop)(struct gc_engine *engine);
    int (*change_scene)(struct gc_engine *engine, gc_scene *scene);

    sfRenderWindow *window;
    void (*draw)(struct gc_engine *engine);
};

gc_engine *engine_create(char *title);
bool engine_is_open(gc_engine *engine);
void handle_events(gc_engine *engine);
int change_scene(gc_engine *engine, gc_scene *scene);