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
    gc_scene *scene = va_arg(args, gc_scene *);
    char *onclick = va_arg(args, char *);
    callback_t callback;

    if (!scene)
        return;
    callback = scene->get_callback(scene, onclick);
    if (!callback)
        my_printf("No callback found with the name: %s\n", onclick);
    cmp->onclick = callback;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct clickable_component *cmp = (struct clickable_component *)component;
    char *onclick = xml_gettempprop(n, "click");
    callback_t callback;

    if (!scene)
        return;
    callback = scene->get_callback(scene, onclick);
    if (!callback)
        my_printf("No callback found with the name: %s\n", onclick);
    cmp->onclick = callback;
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