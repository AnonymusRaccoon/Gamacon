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
#include "components/transform_component.h"
#include "components/texture_renderer.h"
#include <stddef.h>

void tex_rend_update_entity(gc_engine *engine, gc_entity *entity, float dtime)
{
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    struct texture_renderer *text = (struct texture_renderer *)\
entity->get_component(entity, "TextureRenderer");

    if (!text->sprite)
        return;
    text->sprite->pos = pos->position;
    text->sprite->size = pos->size;
    engine->draw_texture(engine, text->sprite);
    (void)dtime;
}

void tex_rend_destroy(void *system)
{
    (void)system;
}

const gc_system texture_renderer_system = {
    name: "TextureRendererSystem",
    component_name: "TextureRenderer",
    check_dependencies: &system_check_dependencies,
    update_entity: &tex_rend_update_entity,
    destroy: &tex_rend_destroy
};