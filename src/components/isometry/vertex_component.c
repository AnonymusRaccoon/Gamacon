/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#include "xml.h"
#include "component.h"
#include "components/vertex_component.h"
#include "create_map_functions.h"
#include "utility.h"
#include <stddef.h>

static void ctr(void *component, va_list args)
{
    (void)component;
    (void)args;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct vertex_component *this = (struct vertex_component *)component;
	char *tilemap = xml_gettempprop(n, "tilemap");
	char *name = n->name;

    this->vertices = NULL;
    this->map = NULL;
    if (!tilemap) {
		my_printf("gamacon: unable to find property 'tilemap' on %s\n", name);
		return;
    }
    n = xml_parse(tilemap);
    if (!n) {
    	my_printf("gamacon: unable to find a valid tilemap at %s\n", tilemap);
    	return;
    }
    if (!get_vertices(this, n->child) || !get_tiles(this, scene, n->child)) {
		my_printf("Unable to malloc during verticies/tile parsing\n");
        return;
    }
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

const struct vertex_component vertex_component = {
    base: {
        name: "vertex_component",
        size: sizeof(struct vertex_component),
        dependencies: (char *[]){
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};