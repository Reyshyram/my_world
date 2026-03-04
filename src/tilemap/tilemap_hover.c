/*
** EPITECH PROJECT, 2026
** tilemap_hover.c
** File description:
** Check if a tile is hovered
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Vertex.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>

#include "tilemap.h"

static float cross_product(sfVector2f *a, sfVector2f *b, sfVector2f *point)
{
    return (b->x - a->x) * (point->y - a->y)
        - (b->y - a->y) * (point->x - a->x);
}

static bool point_in_quad(sfVector2f *point, sfVector2f corners[4])
{
    float distances[4];
    bool is_before_the_right = false;
    bool is_after_the_left = false;

    for (size_t i = 0; i < 4; i++)
        distances[i] =
            cross_product(&corners[i], &corners[(i + 1) % 4], point);
    is_before_the_right = distances[0] < 0 || distances[1] < 0
        || distances[2] < 0 || distances[3] < 0;
    is_after_the_left = distances[0] > 0 || distances[1] > 0
        || distances[2] > 0 || distances[3] > 0;
    return !(is_before_the_right && is_after_the_left);
}

static bool check_tile_hover(tilemap_t *tilemap, sfVector2f *mouse_pos,
    draw_order_t *tile)
{
    sfVector2f corners[4];
    int height = tilemap->heights[tile->y * tilemap->width + tile->x];

    for (size_t i = 0; i < 4; i++)
        corners[i] = project_point(tilemap, tile->x + CORNERS_OFFSETS[i].x,
            tile->y + CORNERS_OFFSETS[i].y, height);
    if (!point_in_quad(mouse_pos, corners))
        return false;
    tilemap->hover_x = tile->x;
    tilemap->hover_y = tile->y;
    return true;
}

static bool is_tile_hovered(tilemap_t *tilemap, sfVector2f *mouse_pos,
    draw_order_t *draw_order)
{
    for (ssize_t i = (ssize_t) (tilemap->height * tilemap->width) - 1; i >= 0;
        i--)
        if (check_tile_hover(tilemap, mouse_pos, &draw_order[i]))
            return true;
    return false;
}

static void update_hover_vertices(tilemap_t *tilemap)
{
    sfVertex vertex = {.color = HOVER_COLOR};
    int height =
        tilemap->heights[tilemap->hover_y * tilemap->width + tilemap->hover_x];

    for (size_t i = 0; i < 4; i++) {
        vertex.position =
            project_point(tilemap, tilemap->hover_x + CORNERS_OFFSETS[i].x,
            tilemap->hover_y + CORNERS_OFFSETS[i].y, height);
        sfVertexArray_append(tilemap->hover_vertices, vertex);
    }
}

void tilemap_update_hover(tilemap_t *tilemap, sfRenderWindow *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f true_mouse_pos =
        sfRenderWindow_mapPixelToCoords(window, mouse_pos, tilemap->view);
    float cos_rot = cosf(tilemap->rotation_rad);
    float sin_rot = sinf(tilemap->rotation_rad);
    sfVector2f view_dir = {cos_rot + sin_rot, cos_rot - sin_rot};
    draw_order_t *draw_order = get_draw_order(tilemap, &view_dir);

    tilemap->is_tile_hovered = false;
    if (!draw_order)
        return;
    tilemap->is_tile_hovered =
        is_tile_hovered(tilemap, &true_mouse_pos, draw_order);
    free(draw_order);
    sfVertexArray_clear(tilemap->hover_vertices);
    if (tilemap->is_tile_hovered)
        update_hover_vertices(tilemap);
}
