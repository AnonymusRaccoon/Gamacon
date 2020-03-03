//
// Created by anonymus-raccoon on 2/21/20.
//

#include "engine.h"
#include "data.h"
#include "xml.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "components/fixed_to_cam_component.h"
#include "components/tag_component.h"
#include "systems/sfml_renderer_system.h"
#include "ui.h"
#include <malloc.h>

gc_entity *new_text(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_entity *entity;

	if (xml_hasproperty(n, "text_id"))
		entity = entity_create_with_id(xml_getintprop(n, "text_id"));
	else
		entity = entity_create();
	entity->add_component(entity, new_component(&transform_component,
		(gc_vector2){0, 0}, (gc_vector2){0, 0}));
	entity->add_component(entity, new_component(&renderer_component,
		GC_TXTREND, xml_getproperty(n, "text"),
		scene->get_data(scene, "font", NULL),
		xml_getintprop(n, "size"),
		xml_gettempprop(n, "color"), xml_getbool(n, "resize", true)));
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){xml_getintprop(n, "x"),xml_getintprop(n, "y")},
		xml_propcontains(n, "x", "%"), xml_propcontains(n, "y", "%"),
		0, 0, false, false));
	if (xml_hasproperty(n, "tag"))
		entity->add_component(entity, new_component(&tag_component,
			xml_getproperty(n, "tag")));
	return (entity);
}

gc_entity *new_sprite(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_entity *entity = entity_create();
	char *src = xml_gettempprop(n, "src");
	sfTexture *texture = scene->get_data(scene, "sprite", src);

	entity->add_component(entity, new_component(&transform_component,
		(gc_vector2){0, 0},
		(gc_vector2){xml_getintprop(n, "width"),xml_getintprop(n, "height")}));
	entity->add_component(entity, new_component(&renderer_component,
		GC_TEXTUREREND, texture, (sfIntRect){0, 0, -1, -1}));
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){xml_getintprop(n, "x"),xml_getintprop(n, "y") },
		xml_propcontains(n, "x", "%"), xml_propcontains(n, "y", "%"),
		xml_getintprop(n, "width"), xml_getintprop(n, "height"),
		xml_propcontains(n, "width", "%"), xml_propcontains(n, "height", "%")));
	if (xml_hasproperty(n, "tag"))
		entity->add_component(entity, new_component(&tag_component,
			xml_getproperty(n, "tag")));
	return (entity);
}

gc_data *sprite_make(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_list *list = NULL;
	gc_data *data = malloc(sizeof(*data));

	LISTADD(list, new_sprite(engine, scene, n));
	data->name = "sprite";
	data->type = "ui";
	data->destroy = NULL;
	data->custom = list;
	return (data);
}

gc_data *text_make(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_list *list = NULL;
	gc_data *data = malloc(sizeof(*data));

	LISTADD(list, new_text(engine, scene, n));
	data->name = "text";
	data->type = "ui";
	data->destroy = NULL;
	data->custom = list;
	return (data);
}

void ui_setup(gc_engine *engine)
{
	engine->add_dataloader(engine, "button", &button_make);
	engine->add_dataloader(engine, "panel", &sprite_make);
	engine->add_dataloader(engine, "text", &text_make);
}