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

bool get_vertices(struct vertex_component *this, node *n);
char *get_texture_for_coords(gc_vector2i coords, node *n);
bool init_tile(struct vertex_component *this, int *inc, void **d, \
gc_vector2i c);
bool get_tiles(struct vertex_component *this, gc_scene *scene, node *n);

#endif //MY3D_CREATE_MAP_FUNCTIONS_H
