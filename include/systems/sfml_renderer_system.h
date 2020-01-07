/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#pragma once

#include "system.h"
#include <SFML/Graphics.h>
#include "scene.h"
#include "systems/sfml_renderer_system.h"
#include "systems/camerafollow_system.h"

struct sfml_renderer_system
{
    gc_system system;
    sfRenderWindow *window;
    sfSprite *sprite;
    sfView *view;
};

gc_system *gc_new_sfml_renderer(gc_engine *engine, \
const char *title, int framerate);
bool sfml_is_open(gc_engine *engine);
bool sfml_has_focus(gc_engine *engine);
bool sfml_is_keypressed(int key);
void sfml_handle_events(gc_engine *engine);
void sfml_draw(gc_engine *engine);
void entities_update_to_cam(gc_scene *scene, \
struct sfml_renderer_system *renderer, struct camerafollow_system *cam);
void entities_update_to_cam_size(gc_scene *scene, gc_vector2 size);

extern const struct sfml_renderer_system sfml_renderer;