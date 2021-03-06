/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** tooltip
*/


#include "engine.h"
#include "xml.h"
#include "ui.h"
#include <stddef.h>
#include "components/tag_component.h"
#include "components/fixed_to_cam_component.h"
#include "components/tooltip_component.h"
#include "components/renderer.h"
#include "components/transform_component.h"

static void setup_position(gc_entity *entity, gc_scene *scene, node *n)
{
    entity->add_component(entity, new_component(&fixed_to_cam,
        entity,
        (gc_vector2){
        xml_getintprop(n, "x") + xml_getintprop(n, "tooltip_x"),
        xml_getintprop(n, "y") - xml_getintprop(n, "tooltip_y")
        },
        xml_propcontains(n, "x", "%"),
        xml_propcontains(n, "y", "%"),
        0, 0, false, false));
}

gc_entity *tooltip_make(gc_engine *engine, gc_scene *scene, node *n, \
gc_entity *parent)
{
    gc_entity *entity = entity_create();

    if (!entity)
        return (NULL);
    entity->add_component(entity, new_component(&transform_component,
        (gc_vector2){0, 0}, (gc_vector2){0, 0}));
    entity->add_component(entity, new_component(&renderer_component,
        GC_TXTREND, xml_getproperty(n, "tooltip"),
        scene->get_data(scene, "font", NULL), xml_getintprop(n, "size"),
        xml_gettempprop(n, "color"), xml_getbool(n, "resize", true)));
    setup_position(entity, scene, n);
    entity->add_component(entity, new_component(&tooltip_component,
        GETCMP(parent, transform_component), xml_getfloatprop(n, "padding_x"),
        xml_getfloatprop(n, "padding_y"), xml_getbool(n, "centered", true)));
    if (xml_hasproperty(n, "tag"))
        entity->add_component(entity, new_component(&tag_component,
            xml_getproperty(n, "tag")));
    return (entity);
}