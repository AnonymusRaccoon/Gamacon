/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parralax_component
*/

#include "components/tooltip_component.h"
#include "xml.h"
#include "my.h"

static void ctr(void *component, va_list args)
{
	struct tooltip_component *cmp = (struct tooltip_component *)component;

	cmp->parent_transform = va_arg(args, struct transform_component *);
	cmp->padding.x = va_arg(args, double);
	cmp->padding.y = va_arg(args, double);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
	my_printf("Can't create a tooltip component from the fdctr.\n");
}

static void dtr(void *component)
{
}

static char *serialize(void *component)
{
	(void)component;
	return (NULL);
}

const struct tooltip_component tooltip_component = {
	base: {
		name: "tooltip_component",
		size: sizeof(struct tooltip_component),
		dependencies: (char *[]) {"renderer", NULL},
		ctr: &ctr,
		fdctr: &fdctr,
		dtr: &dtr,
		serialize: &serialize,
		destroy: &component_destroy
	}
};