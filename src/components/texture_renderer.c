/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#include "engine.h"
#include "components/position_component.h"
#include "components/texture_renderer.h"

static void texture_rend_ctr(void *component, va_list args)
{
    struct texture_renderer *cmp = (struct texture_renderer *)component;

    cmp->texture = va_arg(args, gc_texture *);
}

static void texture_rend_fdctr(gc_engine *engine, void *component, char *args)
{
    struct texture_renderer *cmp = (struct texture_renderer *)component;

    cmp->texture = get_texture(engine, args);
}

static void texture_rend_dtr(void *component)
{
    (void)component;
}

static char *texture_rend_serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct texture_renderer texture_renderer = {
    base: {
        name: "TextureRenderer",
        size: sizeof(struct texture_renderer),
        dependencies: (void *){ &position_component, NULL },
        ctr: &texture_rend_ctr,
        fdctr: &texture_rend_fdctr,
        dtr: &texture_rend_dtr,
        serialize: &texture_rend_serialize,
        destroy: &component_destroy,
        next: NULL,
        prev: NULL
    },
    texture: NULL,
};