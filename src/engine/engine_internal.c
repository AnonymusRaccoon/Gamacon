/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine_internal
*/

#include <stdbool.h>
#include "engine.h"

 bool engine_is_open(gc_engine *engine)
 {
     return (sfRenderWindow_isOpen(engine->window));
 }

 int change_scene(gc_engine *engine, gc_scene *scene)
 {
     (void)engine;
     (void)scene;
     return (0);
 }