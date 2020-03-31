/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_linker.c
*/

#include <components/renderer.h>
#include "component.h"
#include "components/vertex_component.h"
#include "map_utils.h"
#include "my.h"


static void ctr(void *component, va_list args)
{
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *vert;
    int x = xml_getintprop(n, "x");
    int y = xml_getintprop(n, "y");
    struct tile *tile;
    struct renderer *rend;

    if (!maps)
        return;
    vert = GETCMP(maps->data, vertex_component);
    tile = get_tile_at(vert, (gc_vector2i){x, y});
    if (!tile) {
        my_printf("No tile found at %d, %d. Can't link entity to it.\n", x, y);
        return;
    }
    tile->entity = entity;
    rend = GETCMP(entity, renderer);
    if (rend)
        rend->is_visible = false;
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const gc_component map_linker = {
    name: "map_linker",
    size: sizeof(gc_component),
    dependencies: (char *[]) {
        NULL
    },
    ctr: &ctr,
    fdctr: &fdctr,
    dtr: &dtr,
    serialize: &serialize,
    destroy: &component_destroy
};