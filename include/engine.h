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
#include "sprite.h"
#include <stdbool.h>
#include <SFML/Graphics.h>

struct gc_engine
{
    gc_scene *scene;
    bool (*is_open)(gc_engine *engine);
    int (*game_loop)(gc_engine *engine);
    int (*change_scene)(gc_engine *engine, gc_scene *scene);
    void (*draw_texture)(gc_engine *, gc_sprite *);
    void (*destroy)(gc_engine *engine);

    gc_list *systems;
    void (*add_system)(gc_engine *engine, const gc_system *system);
    const gc_system *(*get_system)(gc_engine *engine, const char *name);
    gc_list *components;
    void (*add_component)(gc_engine *engine, const void *component);
    const void *(*get_component)(gc_engine *engine, const char *name);

    sfRenderWindow *window;
    sfSprite *sprite;
    sfClock *clock;
    void (*draw)(gc_engine *engine);
};

gc_engine *engine_create(char *title, unsigned framerate);
bool engine_is_open(gc_engine *engine);
void handle_events(gc_engine *engine);
int change_scene(gc_engine *engine, gc_scene *scene);

void engine_add_buildin_systems(gc_engine *engine);
const gc_system *engine_get_system(gc_engine *engine, const char *name);
void engine_add_system(gc_engine *engine, const gc_system *system);

void engine_add_buildin_components(gc_engine *engine);
const void *engine_get_component(gc_engine *engine, const char *name);
void engine_add_component(gc_engine *engine, const void *component);