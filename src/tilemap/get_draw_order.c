/*
** EPITECH PROJECT, 2026
** get_draw_order.c
** File description:
** Sort the tiles by drawing order
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>

#include "tilemap.h"

static int compare_draw_order(const void *a, const void *b)
{
    float order_a = ((const draw_order_t *) a)->order;
    float order_b = ((const draw_order_t *) b)->order;

    if (order_a < order_b)
        return -1;
    if (order_a > order_b)
        return 1;
    return 0;
}

draw_order_t *get_draw_order(const tilemap_t *tilemap,
    const sfVector2f *view_dir)
{
    size_t nb_tiles = tilemap->width * tilemap->height;
    draw_order_t *order = malloc(sizeof(draw_order_t) * nb_tiles);

    if (!order)
        return nullptr;
    for (size_t y = 0; y < tilemap->height; y++)
        for (size_t x = 0; x < tilemap->width; x++)
            order[y * tilemap->width + x] = (draw_order_t) {
                x,
                y,
                (float) x * view_dir->x + (float) y * view_dir->y,
            };
    qsort(order, nb_tiles, sizeof(*order), compare_draw_order);
    return order;
}
