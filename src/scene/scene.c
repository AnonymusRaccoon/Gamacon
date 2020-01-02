/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include "utility.h"
#include "texture.h"
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

int scene_load_textures(gc_scene *scene, node *n)
{
    gc_texture *texture;
    int len;
    int i = 0;
    char *src;

    n = xml_getnode(n, "textures");
    if (!n)
        return (0);
    len = xml_getchildcount(n);
    scene->textures = malloc(sizeof(gc_texture) * (len + 1));
    for (n = n->child; n; n = n->next) {
        src = xml_getproperty(n, "src");
        if (!src || !(texture = texture_create(src)))
            return (-1);
        scene->textures[i] = texture;
        i++;
    }
    scene->textures[len] = NULL;
    return (0);
}

gc_scene *scene_create(gc_engine *engine, const char *xmlpath)
{
    gc_scene *scene = malloc(sizeof(gc_scene));
    node *n = NULL;

    if (!scene)
        return (NULL);
    scene->textures = NULL;
    if (xmlpath && !(n = xml_parse(xmlpath)))
        return (NULL);
    if (scene_load_textures(scene, n) < 0)
        return (NULL);
    scene->entities = NULL;
    scene->entities_by_cmp = NULL;
    scene->add_entity = &entity_add;
    scene->get_entity = &entity_get;
    scene->get_entity_by_cmp = &get_entity_by_cmp;
    scene->destroy = &scene_destroy;
    prefab_loadentities(n, engine, scene);
    xml_destroy(n);
    return (scene);
}

int change_scene(gc_engine *engine, gc_scene *scene)
{
    if (engine->scene)
        engine->scene->destroy(engine->scene);
    engine->scene = scene;
    return (0);
}

void scene_destroy(gc_scene *scene)
{
    gc_list *next = NULL;
    gc_tupple *tup = scene->entities_by_cmp;

    for (gc_list *entity = scene->entities; entity; entity = next) {
        next = entity->next;
        ((gc_entity *)entity->data)->destroy(entity->data);
        free(entity);
    }
    for (int i = 0; scene->textures[i]; i++)
        scene->textures[i]->destroy(scene->textures[i]);
    free(scene->textures);
    for (gc_tupple *tupple = tup; tupple; tupple = tup) {
        tup = tupple->next;
        for (gc_list *li = tupple->entities; li; li = next) {
            next = li->next;
            free(li);
        }
        free(tupple->name);
        free(tupple);
    }
    free(scene);
}