/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#ifndef MY3D_CREATE_MAP_FUNCTIONS_H
#define MY3D_CREATE_MAP_FUNCTIONS_H

#include <stdbool.h>
#include "components/vertex_component.h"
#include "systems/sfml_renderer_system.h"

bool get_vertices(struct vertex_component *this, node *n);
bool get_tiles(struct vertex_component *this, gc_scene *scene, node *n);
void isometry_update_entity(struct sfml_renderer_system *this, \
gc_entity *entity, gc_engine *engine, float dt);

#endif //MY3D_CREATE_MAP_FUNCTIONS_H
