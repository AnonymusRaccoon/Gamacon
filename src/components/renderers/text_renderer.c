/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sprite_renderer
*/

#include "components/renderer.h"
#include "vector2.h"
#include "xml.h"
#include "sprite.h"
#include "text.h"
#include <malloc.h>
#include <SFML/Graphics.h>

void text_ctr(struct renderer *cmp, va_list args)
{
    gc_text *gctext = malloc(sizeof(gc_text));

    if (!gctext)
        return;
    cmp->data = gctext;
    gctext->text = va_arg(args, char *);
    gctext->font = va_arg(args, sfFont *);
    cmp->type = GC_TXTREND;
}

void text_fdctr(gc_scene *scene, struct renderer *cmp, node *n)
{
    gc_text *gctext = malloc(sizeof(gc_text));

    if (!gctext)
        return;
    cmp->data = gctext;
    gctext->text = xml_getproperty(n, "text");
    if (!gctext->text)
        return;
    gctext->font = scene->get_data(scene, "font", xml_getproperty(n, "src"));
    cmp->type = GC_TXTREND;
}
