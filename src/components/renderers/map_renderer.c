/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** map_renderer
*/

#include "components/renderer.h"
#include "components/vertex_component.h"
#include "vector2.h"
#include "sprite.h"
#include "entity.h"
#include "xml.h"
#include "my.h"
#include <malloc.h>

void map_ctr(struct renderer *cmp, va_list args)
{
    cmp->data = va_arg(args, struct vertex_component *);
}

void map_fdctr(gc_scene *scene, struct renderer *cmp, gc_entity *entity)
{
    (void)scene;
    cmp->data = GETCMP(vertex_component);
    if (!cmp->data)
        my_printf("Gamacon: missing component \"vertext component\" from \
the entity with id: %d\n", entity->id);
}