/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** map utilities
*/

#include "vertex_component.h"
#include "renderer.h"

void set_entity_ptr_to_tile(gc_entity *entity, struct tile *tile)
{
    struct renderer *renderer;
    tile->entity = entity;

    if (!entity)
        return;
    renderer = entity->get_component(entity, "renderer");
    renderer->is_visible = false;
}