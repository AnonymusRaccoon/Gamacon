/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine_internal
*/

#include <stdbool.h>
#include "engine.h"

 bool engine_is_open(gcEngine *engine)
 {
     return (sfRenderWindow_isOpen(engine->renderer.window));
 }

 int change_scene(gcEngine *engine, gcScene *scene)
 {
     (void)engine;
     (void)scene;
     return (0);
 }