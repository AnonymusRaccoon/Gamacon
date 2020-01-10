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
#include <malloc.h>
#include <SFML/Graphics.h>

void text_ctr(struct renderer *cmp, va_list args)
{
    // char *txt;
    // gc_text *gctext = malloc(sizeof(gc_text));

    // if (!gctext)
    //     return;
    // cmp->data = gctext;
    // gctext->text = sfText_create();
    // if (!gctext->text)
    //     return;
    // gctext->font = va_arg(args, sfFont *);
    // if (gctext->font)
    //     sfText_setFont(gctext->text, gctext->font);
    // txt = va_arg(args, char *);
    // if (txt)
    //     sfText_setString(gctext->text, txt);
    // cmp->type = GC_TXTREND;
}

void text_fdctr(gc_scene *scene, struct renderer *cmp, node *n)
{
    // gc_text *gctext = malloc(sizeof(gc_text));

    // if (!gctext)
    //     return;
    // cmp->data = gctext;
    // gctext->text = sfText_create();
    // if (!gctext->text)
    //     return;
    // gctext->font = scene->get_data(scene, "font", xml_getproperty(n, "src"));
    // if (gctext->font)
    //     sfText_setFont(gctext->text, gctext->font);
    // sfText_setString(gctext->text, xml_getproperty(n, "text"));
    // cmp->type = GC_TXTREND;
}
