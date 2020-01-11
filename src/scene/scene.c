/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include "utility.h"
#include "prefab.h"
#include <stdlib.h>

gc_list *get_entity_by_cmp(gc_scene *scene, const char *cmp_name)
{
    for (gc_tupple *tup = scene->entities_by_cmp; tup; tup = tup->next) {
        if (!my_strcmp(tup->name, cmp_name))
            return (tup->entities);
    }
    return (NULL);
}

void *scene_get_data(gc_scene *scene, const char *type, const char *name)
{
    gc_data *data;

    if (!scene || !scene->data)
        return (NULL);
    for (gc_list *li = scene->data; li; li = li->next) {
        data = (gc_data *)li->data;
        if (type && my_strcmp(data->type, type))
            continue;
        if (!name || !my_strcmp(data->name, name))
            return (data->custom);
    }
    return (NULL);
}

gc_scene *scene_create(gc_engine *engine, const char *xmlpath)
{
    gc_scene *scene = malloc(sizeof(gc_scene));
    node *n = NULL;

    if (!scene)
        return (NULL);
    if (xmlpath && !(n = xml_parse(xmlpath)))
        return (NULL);
    scene_load_data(engine, scene, n);
    scene->entities = NULL;
    scene->entities_by_cmp = NULL;
    scene->add_entity = &entity_add;
    scene->get_entity = &entity_get;
    scene->get_entity_by_cmp = &get_entity_by_cmp;
    scene->destroy = &scene_destroy;
    scene->get_data = &scene_get_data;
    prefab_loadentities(n, engine, scene);
    xml_destroy(n);
    return (scene);
}

int change_scene(gc_engine *engine, gc_scene *scene)
{
    void *music = scene->get_data(scene, "music", NULL);

    engine->stop_music(engine);
    if (engine->scene)
        engine->scene->destroy(engine->scene);
    engine->scene = scene;
    if (music)
        engine->play_music(music);
    return (0);
}