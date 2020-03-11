/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#include "xml.h"
#include "component.h"
#include "components/vertex_component.h"
#include "utility.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static bool get_vertices(void *component, node *n)
{
    struct vertex_component *this = (struct vertex_component *)component;
    int i = 0;
    int j = 0;
    int size[3] = {sizeof(struct vertex), sizeof(struct vertex *), 0};

    this->vertices = malloc(size[1] * (xml_getchildcount(n) + 1));
    if (!this->vertices)
        return (false);
    for (node *line = n->child; line; line = line->next) {
        this->vertices[i] = malloc(size[0] * (xml_getchildcount(line) + 1));
        if (!this->vertices[i])
            return (false);
        for (node *row = line->child; row; row = row->next) {
            size[2] = xml_getintprop(row, "height");
            this->vertices[i][j] = (struct vertex){i, j++, size[2]};
        }
        this->vertices[i++][j] = (struct vertex){0, 0, INT32_MIN};
        j = 0;
    }
    this->vertices[i] = NULL;
    return (true);
}

static bool get_tiles(struct vertex_component *this, gc_scene *scene, node *n)
{
    int inc = 0;
    int v_x = xml_getchildcount(n);
    int vy = xml_getchildcount(n->child);

	for (node *line = n->child; line; line = line->next)
		vy = (xml_getchildcount(line) > vy) ? xml_getchildcount(line) : vy;
    this->map = malloc(sizeof(struct tile) * (v_x * vy + 1));
    if (!this->map)
        return (false);
    for (v_x = 0; this->vertices[v_x + 1]; v_x++) {
        for (vy = 0; this->vertices[v_x][vy].z != INT32_MIN; vy++) {
			if (this->vertices[v_x][vy].z == INT32_MIN || \
			this->vertices[v_x][vy + 1].z == INT32_MIN || \
			this->vertices[v_x + 1][vy].z == INT32_MIN || \
			this->vertices[v_x + 1][vy + 1].z == INT32_MIN)
				break;
            this->map[inc].corners[0] = &this->vertices[v_x][vy];
            this->map[inc].corners[1] = &this->vertices[v_x][vy + 1];
            this->map[inc].corners[3] = &this->vertices[v_x + 1][vy];
            this->map[inc].corners[2] = &this->vertices[v_x + 1][vy + 1];
            this->map[inc].data = 0;
            this->map[inc++].texture = scene->get_data(scene, "sprite", (inc % 2) ? "cobblestone" : "mossy_cobblestone");
            if (inc == 60)
				this->map[inc - 1].texture = scene->get_data(scene, "sprite", "comparator_on");
            if (inc > 31 && inc < 56)
                this->map[inc - 1].texture = scene->get_data(scene, "sprite", "crafting_table");
        }
    }
    this->map[inc].corners[0] = NULL;
    return (true);
}

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
    if (!get_vertices(component, n) || !get_tiles(this, scene, n)) {
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