/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** keyboard_controller
*/


#include "xml.h"
#include "component.h"
#include "components/controllable_component.h"
#include "components/controllers/keyboard_controller.h"
#include "utility.h"
#include <stdlib.h>

static void ctr(void *component, va_list args)
{
    struct keyboard_controller *cmp = (struct keyboard_controller *)\
component;

    cmp->left_key = va_arg(args, int);
    cmp->right_key = va_arg(args, int);
    cmp->jump_key = va_arg(args, int);
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct keyboard_controller *cmp = (struct keyboard_controller *)\
component;

    cmp->left_key = xml_getintprop(n, "left");
    cmp->right_key = xml_getintprop(n, "right");
    cmp->jump_key = xml_getintprop(n, "jump");
    (void)scene;
    (void)entity;
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

const struct keyboard_controller keyboard_controller = {
    base: {
        name: "keyboard_controller",
        size: sizeof(struct keyboard_controller),
        dependencies: (char *[]){
            "movable_component",
            "transform_component",
            "controllable_component",
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    },
    left_key: 16,
    right_key: 3,
    jump_key: 57
};