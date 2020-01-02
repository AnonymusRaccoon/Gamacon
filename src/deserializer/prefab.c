/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

#include "xml.h"
#include "engine.h"
#include "entity.h"
#include "prefab.h"
#include "read_line.h"
#include "utility.h"
#include <unistd.h>
#include <fcntl.h>

int prefab_load(gc_engine *engine, const char *path)
{
    node *n;

    if (!engine || !engine->scene)
        return (-1);
    n = xml_parse(path);
    if (!n || prefab_loadentities(n, engine, engine->scene) < 0)
        return (-1);
    xml_destroy(n);
    return (0);
}

int prefab_loadentities(node *n, gc_engine *engine, gc_scene *scene)
{
    gc_entity *entity;

    n = xml_getnode(n, "gc_entities");
    if (!n)
        return (-1);
    for (node *ent_n = n->child; ent_n; ent_n = ent_n->next) {
        entity = deserialize_entity(engine, scene, ent_n);
        if (!entity)
            return (-1);
        scene->add_entity(scene, entity);
    }
    return (0);
}