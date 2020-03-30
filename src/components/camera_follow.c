/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** camera_follow
*/

#include "xml.h"
#include "component.h"

static void ctr(void *component, va_list args)
{
    (void)component;
    (void)args;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    (void)scene;
    (void)entity;
    (void)component;
    (void)n;
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

const gc_component camerafollow_component = {
    name: "camerafollow_component",
    size: sizeof(struct gc_component),
    dependencies: (char *[]){
        "transform_component",
        NULL
    },
    ctr: &ctr,
    fdctr: &fdctr,
    dtr: &dtr,
    serialize: &serialize,
    destroy: &component_destroy
};