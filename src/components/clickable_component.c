/*
** EPITECH PROJECT, 2020
** Gamacon's button
** File description:
** clickable_component
*/

#include "xml.h"
#include "component.h"
#include "engine.h"
#include "components/clickable_component.h"
#include "utility.h"

static void ctr(void *component, va_list args)
{
	struct clickable_component *cmp = (struct clickable_component *)component;
	gc_engine *engine = va_arg(args, gc_engine *);
	char *onclick = va_arg(args, char *);

	if (!engine)
		return;
	cmp->onclick = engine->get_callback(engine, onclick);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
	(void)entity;
	(void)scene;
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

const struct clickable_component clickable_component = {
	base: {
		name: "clickable_component",
		size: sizeof(struct clickable_component),
		dependencies: (char *[]){"transform_component", NULL},
		ctr: &ctr,
		fdctr: &fdctr,
		dtr: &dtr,
		serialize: &serialize,
		destroy: &component_destroy
	}
};