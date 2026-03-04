/*
** EPITECH PROJECT, 2026
** tilemap_calculate_vertices.c
** File description:
** Calculate the vertices of the tilemap
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Vertex.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdlib.h>

#include "tilemap.h"

void add_tile_side(sfVertexArray *vertex_array, const sfVector2f corners[4],
    const sfColor *color)
{
    sfVertex vertex = {.color = *color};

    for (size_t i = 0; i < 4; i++) {
        vertex.position = corners[i];
        sfVertexArray_append(vertex_array, vertex);
    }
}

static void calculate_corners_pos(const tilemap_t *map,
    tile_render_t *tile_render, const draw_order_t *tile)
{
    for (int i = 0; i < 4; i++)
        tile_render->corners[i] =
            project_point(map, tile->x + CORNERS_OFFSETS[i].x,
            tile->y + CORNERS_OFFSETS[i].y, tile_render->tile_height);
}

static void add_tile_vertices(const tilemap_t *tilemap,
    tile_render_t *tile_render, const draw_order_t *tile,
    const sfVector2f *view_dir)
{
    size_t index = tile->y * tilemap->width + tile->x;

    tile_render->tile_height = tilemap->heights[index];
    tile_render->tile_type = tilemap->types[index];
    calculate_corners_pos(tilemap, tile_render, tile);
    add_visible_walls(tilemap, tile_render, tile, view_dir);
    add_tile_side(tile_render->vertices, tile_render->corners,
        &TILE_COLORS[tile_render->tile_type]);
}

void tilemap_calculate_vertices(tilemap_t *tilemap)
{
    tile_render_t tile_render = {.vertices = tilemap->vertices};
    float cos_rotation = cosf(tilemap->rotation_rad);
    float sin_rotation = sinf(tilemap->rotation_rad);
    sfVector2f view_dir = {cos_rotation + sin_rotation,
        cos_rotation - sin_rotation};
    draw_order_t *draw_order = get_draw_order(tilemap, &view_dir);

    if (!draw_order)
        return;
    sfVertexArray_clear(tilemap->vertices);
    for (size_t i = 0; i < tilemap->width * tilemap->height; i++)
        add_tile_vertices(tilemap, &tile_render, &draw_order[i], &view_dir);
    free(draw_order);
}
