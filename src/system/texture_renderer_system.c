/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"

void tex_rend_update_entity(const gc_entity *entity)
{
    (void)entity;
}

const gc_system texture_renderer_system = {
    name: "TextureRendererSystem",
    component_name: "TextureRenderer",
    check_dependencies: &system_check_dependencies,
    update_entity: &tex_rend_update_entity
};