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
#include "utility.h"

int prefab_load(gc_engine *engine, const char *path)
{
    node *n;
    int prefab_id;

    if (!engine || !engine->scene)
        return (-1);
    n = xml_parse(path);
    prefab_id = prefab_loadentities(n, engine, engine->scene);
    if (!n || prefab_id < 0)
        return (-1);
    xml_destroy(n);
    return (prefab_id);
}

int prefab_loadentities(node *n, gc_engine *engine, gc_scene *scene)
{
    gc_entity *entity;
    static int prefab_id = 0;

    n = xml_getnode(n, "gc_entities");
    if (!n)
        return (-1);
    for (node *ent_n = n->child; ent_n; ent_n = ent_n->next) {
        if (my_strcmp(ent_n->name, "gc_entity")) {
            scene->load_entity(scene, engine, ent_n, prefab_id);
            continue;
        }
        entity = deserialize_entity(engine, scene, ent_n);
        if (!entity)
            return (-1);
        entity->prefab_id = prefab_id;
        scene->add_entity(scene, entity);
    }
    prefab_id++;
    if (engine->on_resize && engine->get_screen_size && engine->scene)
        engine->on_resize(engine, engine->get_screen_size(engine));
    return (prefab_id - 1);
}