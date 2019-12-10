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
    gc_entity *entity;

    if (!engine || !engine->scene)
        return (-1);
    n = xml_parse(path);
    if (!n)
        return (-1);
    for (node *ent_n = n->child; ent_n; ent_n = ent_n->next) {
        entity = deserialize_entity(engine, ent_n);
        if (!entity)
            return (-1);
        engine->scene->add_entity(engine->scene, entity);
    }
    xml_destroy(n);
    return (0);
}
