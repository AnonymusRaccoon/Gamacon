/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"
#include "systems/texture_renderer_system.h"

void tex_rend_update_entity(const gc_entity *entity)
{
    struct position_component *pos = (struct position_component *)entity->get_component(entity, "PositionComponent");
}

const gc_system texture_renderer_system = {
    name: "TextureRendererSystem",
    component_name: "TextureRenderer",
    check_dependencies: &system_check_dependencies,
    update_entity: &tex_rend_update_entity
};