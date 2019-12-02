/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#pragma once

#include "scene.h"
#include "renderer.h"
#include <stdbool.h>

typedef struct gcEngine
{
    gcRenderer renderer;
    gcScene *scene;
    bool (*is_open)();
    int (*game_loop)(struct gcEngine *engine);
    int (*change_scene)(struct gcEngine *engine, gcScene *scene);
} gcEngine;

gcEngine *create_engine(char *title);
bool engine_is_open(gcEngine *engine);
int change_scene(gcEngine *engine, gcScene *scene);