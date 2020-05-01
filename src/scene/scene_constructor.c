/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** scene_constructor.c
*/

#include "scene.h"
#include "prefab.h"
#include "xml.h"
#include <malloc.h>

gc_scene *scene_new(gc_engine *engine)
{
    gc_scene *scene = malloc(sizeof(gc_scene));

    if (!scene)
        return (NULL);
    scene->is_paused = false;
    scene->entities = NULL;
    scene->entities_by_cmp = NULL;
    scene->add_entity = &entity_add;
    scene->get_entity = &entity_get;
    scene->get_entity_by_cmp = &get_entity_by_cmp;
    scene->destroy = &scene_destroy;
    scene->get_data = &scene_get_data;
    scene->get_data_ptr = &scene_get_data_ptr;
    scene->get_callback = &scene_get_callback;
    scene->load_entity = &scene_load_entity;
    scene->callbacks = engine->callbacks;
    scene->data = NULL;
}

gc_scene *scene_parse_xml(gc_scene *scene, gc_engine *engine, const char *xml)
{
    node *n = NULL;

    if (!scene || (xml && !(n = xml_parse(xml))))
        return (NULL);
    scene_load_data(engine, scene, n);
    prefab_loadentities(n, engine, scene);
    xml_destroy(n);
    return (scene);
}

gc_scene *scene_create(gc_engine *engine, const char *xml)
{
    gc_scene *scene = scene_new(engine);
    return (scene_parse_xml(scene, engine, xml));
}