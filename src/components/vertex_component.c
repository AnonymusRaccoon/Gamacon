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
        this->vertices[i] = malloc(size[0] * (xml_getchildcount(n->child) + 1));
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

    this->map = malloc(sizeof(struct tile) * (v_x * vy + 1));
    if (!this->map)
        return (false);
    for (v_x = 0; this->vertices[v_x + 1]; v_x++) {
        for (vy = 0; this->vertices[v_x][vy].z != INT32_MIN; vy++) {
            this->map[inc].corners[0] = &this->vertices[v_x][vy];
            this->map[inc].corners[1] = &this->vertices[v_x][vy + 1];
            this->map[inc].corners[2] = &this->vertices[v_x + 1][vy];
            this->map[inc].corners[3] = &this->vertices[v_x + 1][vy + 1];
            this->map[inc++].texture = scene->get_data(scene, "sprite", (inc % 2) ? "cobblestone" : "mossy_cobblestone");
            if (inc > 31 && inc < 56)
                this->map[inc - 1].texture = scene->get_data(scene, "sprite", "crafting_table");
        }
    }
    this->map[inc].corners[0] = &this->vertices[v_x][vy];
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

    this->vertices = NULL;
    n = xml_parse(xml_gettempprop(n, "tilemap"));
    if (!n) {
    	return;
    }
    if (!get_vertices(component, n)) {
        return;
    }
    if (!get_tiles(this, scene, n)) {
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