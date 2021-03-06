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
#include "my.h"
#include <malloc.h>
#include <SFML/Graphics.h>

void destroy_text_renderer(struct renderer *cmp)
{
    free(((gc_text *)cmp->data)->text);
    free(cmp->data);
}

void text_safe_destroy(struct renderer *rend)
{
    free(rend->data);
}

int color_from_text(char *txt)
{
    if (txt == NULL)
        return (*(int *)&sfWhite);
    if (!my_strcmp(txt, "black"))
        return (*(int *)&sfBlack);
    if (!my_strcmp(txt, "white"))
        return (*(int *)&sfWhite);
    return (*(int *)&sfWhite);
}

void text_ctr(struct renderer *cmp, va_list args)
{
    gc_text *gctext = malloc(sizeof(gc_text));

    if (!gctext)
        return;
    cmp->data = gctext;
    cmp->destroy = &destroy_text_renderer;
    gctext->text = va_arg(args, char *);
    gctext->font = va_arg(args, sfFont *);
    gctext->size = va_arg(args, int);
    gctext->color = color_from_text(va_arg(args, char *));
    gctext->resize = va_arg(args, int);

    if (gctext->size <= 0)
        gctext->size = 30;
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
    cmp->destroy = &destroy_text_renderer;
    gctext->font = scene->get_data(scene, "font", xml_getproperty(n, "src"));
    gctext->size = 30;
    gctext->color = *(int *)&sfWhite;
    gctext->resize = true;
}
