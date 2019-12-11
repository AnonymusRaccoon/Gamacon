/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/
typedef struct gc_engine gc_engine;

#pragma once

#include "xml.h"
#include "scene.h"
#include "vector2.h"
#include "texture.h"
#include "system.h"
#include "list.h"
#include <stdbool.h>

struct gc_engine
{
    gc_scene *scene;
    bool (*is_open)(gc_engine *engine);
    bool (*has_focus)(gc_engine *engine);
    bool (*is_keypressed)(int key);
    void (*handle_events)(gc_engine *engine);
    int (*game_loop)(gc_engine *engine, float dtime);
    void (*draw)(gc_engine *engine);
    int (*change_scene)(gc_engine *engine, gc_scene *scene);
    void (*destroy)(gc_engine *engine);

    gc_list *systems;
    void (*add_system)(gc_engine *engine, const gc_system *system);
    const gc_system *(*get_system)(gc_engine *engine, const char *name);

    gc_list *components;
    void (*add_component)(gc_engine *engine, const void *component);
    const void *(*get_component)(gc_engine *engine, const char *name);
};

gc_engine *engine_create();
bool engine_is_open(gc_engine *engine);
bool engine_has_focus(gc_engine *engine);
bool engine_is_keypressed(int key);
void handle_events(gc_engine *engine);
void engine_draw(gc_engine *engine);
int change_scene(gc_engine *engine, gc_scene *scene);

void engine_add_buildin_systems(gc_engine *engine);
const gc_system *engine_get_system(gc_engine *engine, const char *name);
void engine_add_system(gc_engine *engine, const gc_system *system);

void engine_add_buildin_components(gc_engine *engine);
const void *engine_get_component(gc_engine *engine, const char *name);
void engine_add_component(gc_engine *engine, const void *component);

int engine_use_sfml(gc_engine *engine, const char *title, int framerate);