/*
** EPITECH PROJECT, 2026
** add_walls.c
** File description:
** Add the visible walls to the vertex array
*/

#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <stddef.h>

#include "tilemap.h"

static sfColor darken_color(const sfColor *color, float factor)
{
    return (sfColor) {
        (int) ((float) color->r * factor),
        (int) ((float) color->g * factor),
        (int) ((float) color->b * factor),
        color->a,
    };
}

static tile_type_t get_wall_type(tile_type_t tile_type)
{
    if (tile_type == TILE_TYPE_GRASS)
        return TILE_TYPE_DIRT;
    return tile_type;
}

static int get_neighbor_height(const tilemap_t *tilemap, int x, int y)
{
    if (x < 0 || y < 0 || (size_t) x >= tilemap->width
        || (size_t) y >= tilemap->height)
        return 0;
    return tilemap->heights[y * tilemap->width + x];
}

static void add_wall_if_visible(tile_render_t *tile_render, corner_t corner_a,
    corner_t corner_b, const sfColor *color)
{
    float wall_height =
        (float) (tile_render->tile_height - tile_render->neighbor_height)
        * TILE_HEIGHT;
    sfVector2f corners[4];

    if (tile_render->neighbor_height >= tile_render->tile_height)
        return;
    corners[0] = tile_render->corners[corner_a];
    corners[1] = tile_render->corners[corner_b];
    corners[2] = (sfVector2f) {corners[1].x, corners[1].y + wall_height};
    corners[3] = (sfVector2f) {corners[0].x, corners[0].y + wall_height};
    add_tile_side(tile_render->vertices, corners, color);
}

void add_visible_walls(const tilemap_t *tilemap, tile_render_t *tile_render,
    const draw_order_t *tile, const sfVector2f *view_dir)
{
    const int x_corners[2][2] = {{CORNER_BOTTOM_LEFT, CORNER_TOP_LEFT},
        {CORNER_TOP_RIGHT, CORNER_BOTTOM_RIGHT}};
    const int y_corners[2][2] = {{CORNER_TOP_LEFT, CORNER_TOP_RIGHT},
        {CORNER_BOTTOM_RIGHT, CORNER_BOTTOM_LEFT}};
    tile_type_t wall_type = get_wall_type(tile_render->tile_type);
    sfColor x_color = darken_color(&TILE_COLORS[wall_type], X_AXIS_DARKEN);
    sfColor y_color = darken_color(&TILE_COLORS[wall_type], Y_AXIS_DARKEN);
    int dir_x = view_dir->x >= 0 ? 1 : -1;
    int dir_y = view_dir->y >= 0 ? 1 : -1;
    int x_index = dir_x > 0 ? 1 : 0;
    int y_index = dir_y > 0 ? 1 : 0;

    tile_render->neighbor_height =
        get_neighbor_height(tilemap, (int) tile->x + dir_x, (int) tile->y);
    add_wall_if_visible(tile_render, x_corners[x_index][0],
        x_corners[x_index][1], &x_color);
    tile_render->neighbor_height =
        get_neighbor_height(tilemap, (int) tile->x, (int) tile->y + dir_y);
    add_wall_if_visible(tile_render, y_corners[y_index][0],
        y_corners[y_index][1], &y_color);
}
