/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_linker.c
*/

#include "components/renderer.h"
#include "component.h"
#include "components/vertex_component.h"
#include "components/map_linker.h"
#include "map_utils.h"
#include "my.h"


static struct tile *init(gc_entity *entity, struct vertex_component *vert, \
gc_vector2i pos, bool solid)
{
    struct renderer *rend;
    struct tile *tile = get_tile_at(vert, pos);

    if (!tile) {
        my_printf("No tile found at %d, %d. Can't link entity to it.\n", \
pos.x, pos.y);
        return (NULL);
    }
    tile->entity = entity;
    tile->solid = solid;
    rend = GETCMP(entity, renderer);
    if (rend) {
        rend->is_visible = false;
        rend->render_mode_x = RENDER_MODE_REVERSED;
        rend->render_mode_y = RENDER_MODE_REVERSED;
    }
    return (tile);
}

static void ctr(void *component, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    gc_scene *scene = va_arg(args, gc_scene *);
    struct map_linker *cmp = (struct map_linker *)component;
    gc_list *maps;
    struct vertex_component *vert;
    int x = va_arg(args, int);
    int y = va_arg(args, int);
    bool solid = va_arg(args, int);

    cmp->tile = NULL;
    if (!scene || !(maps = scene->get_entity_by_cmp(scene, "vertex_component")))
        return;
    vert = GETCMP(maps->data, vertex_component);
    cmp->tile = init(entity, vert, (gc_vector2i){x, y}, solid);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct map_linker *cmp = (struct map_linker *)component;
    struct vertex_component *vert;
    int x = xml_getintprop(n, "x");
    int y = xml_getintprop(n, "y");
    bool solid = xml_getbool(n, "solid", true);
    struct renderer *renderer = GETCMP(entity, renderer);

    if (!maps)
        return;
    vert = GETCMP(maps->data, vertex_component);
    cmp->tile = init(entity, vert, (gc_vector2i){x, y}, solid);
    if (renderer && xml_hasproperty(n, "centered"))
        renderer->render_mode_x = RENDER_MODE_CENTERED;
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

const struct map_linker map_linker = {
    base: {
        name: "map_linker",
        size: sizeof(struct map_linker),
        dependencies: (char *[]) {
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};