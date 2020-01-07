/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** camera_follow
*/

#include "xml.h"
#include "component.h"
#include "components/controllable_component.h"
#include "components/camerafollow_component.h"
#include "utility.h"
#include <stdlib.h>

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const gc_component fixed_to_cam = {
    name: "fixed_to_cam",
    size: sizeof(struct gc_component),
    dependencies: (char *[]){
        "transform_component",
        NULL
    },
    ctr: NULL,
    fdctr: NULL,
    dtr: NULL,
    serialize: &serialize,
    destroy: &component_destroy
};