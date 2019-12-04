/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "systems/texture_renderer_system.h"
#include "components/position_component.h"
#include "components/texture_renderer.h"

void tex_rend_update_entity(gc_engine *engine, gc_entity *entity)
{
    struct position_component *pos = \
(struct position_component *)entity->get_component(entity, "PositionComponent");
    struct texture_renderer *text = (\
struct texture_renderer *)entity->get_component(entity, "TextureRenderer");

    engine->draw_texture(engine, text->texture, pos->position);
}

const gc_system texture_renderer_system = {
    name: "TextureRendererSystem",
    component_name: "TextureRenderer",
    check_dependencies: &system_check_dependencies,
    update_entity: &tex_rend_update_entity
};