//
// Created by anonymus-raccoon on 3/9/20.
//

#include "engine.h"
#include "xml.h"
#include "ui.h"
#include <stddef.h>
#include "components/tag_component.h"
#include "components/fixed_to_cam_component.h"
#include "components/tooltip_component.h"
#include "components/renderer.h"
#include "components/transform_component.h"

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
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){xml_getintprop(n, "x") + 10,xml_getintprop(n, "y") - 5},
		xml_propcontains(n, "x", "%"), xml_propcontains(n, "y", "%"),
		0, 0, false, false));
	entity->add_component(entity, new_component(&tooltip_component,
		GETCMP(parent, transform_component), xml_getfloatprop(n, "padding_x"),
		xml_getfloatprop(n, "padding_y")));
	if (xml_hasproperty(n, "tag"))
		entity->add_component(entity, new_component(&tag_component,
			xml_getproperty(n, "tag")));
	return (entity);
}