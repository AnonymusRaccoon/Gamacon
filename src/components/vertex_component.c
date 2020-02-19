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

static void ctr(void *component, va_list args)
{
    (void)component;
    (void)args;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct vertex_component *this = (struct vertex_component *)component;
    int i = 0;
    int j = 0;

    this->vertices = NULL;
    n = xml_parse(xml_gettempprop(n, "tilemap"));
    if (!n)
    	return;
    this->vertices = malloc(sizeof(int *) * (xml_getchildcount(n) + 1));
    if (!this->vertices)
        return;
    for (node *line = n->child; line; line = line->next) {
        this->vertices[i] = malloc(sizeof(int) * (xml_getchildcount(line) + 1));
        if (!this->vertices[i])
            return;
        for (node *row = line->child; row; row = row->next) {
            this->vertices[i][j] = xml_getintprop(row, "height");
            j++;
        }
        this->vertices[i][j] = INT32_MIN;
        i++;
        j = 0;
    }
    this->vertices[i] = NULL;
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