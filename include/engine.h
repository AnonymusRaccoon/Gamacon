/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/
typedef struct gc_engine gc_engine;

#pragma once

#include "scene.h"
#include "vector2.h"
#include "texture.h"
#include "system.h"
#include "list.h"
#include <stdbool.h>
#include <SFML/Graphics.h>

struct gc_engine
{
    gc_scene *scene;
    bool (*is_open)(gc_engine *engine);
    int (*game_loop)(gc_engine *engine);
    int (*change_scene)(gc_engine *engine, gc_scene *scene);
    void (*draw_texture)(gc_engine *, gc_texture *, gc_vector2, gc_vector2);
    void (*destroy)(gc_engine *engine);

    gc_list *systems;
    void (*add_system)(gc_engine *engine, const gc_system *system);

    sfRenderWindow *window;
    sfSprite *sprite;
    void (*draw)(gc_engine *engine);
};

gc_engine *engine_create(char *title, unsigned framerate);
bool engine_is_open(gc_engine *engine);
void handle_events(gc_engine *engine);
int change_scene(gc_engine *engine, gc_scene *scene);

void engine_add_buildin_systems(gc_engine *engine);
void engine_add_system(gc_engine *engine, const gc_system *system);