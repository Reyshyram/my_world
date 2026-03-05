/*
** EPITECH PROJECT, 2026
** tilemap_bomb
** File description:
** simulates a bomb at the selected tile
*/

#include <stddef.h>

#include "tilemap.h"

/*     if (pos > map->width)
        div += 1;
    if (pos < (map->height - 1) * map->width)
        div += 1;
    if (pos % map->width > 0)
        div += 1;
    if (pos % map->width < map->width)
        div += 1;
*/

static void lower_tile_at_pos(tilemap_t *map, size_t x_pos, size_t y_pos,
    size_t clicked_pos)
{
    map->heights[clicked_pos + x_pos + y_pos * map->width] -= 1;
}

static void bomb_check_loop(tilemap_t *map, int x_pos, int y_pos, int range)
{
    size_t position = map->clicked_x + map->clicked_y * map->width;

    if (x_pos + y_pos < range) {
        lower_tile_at_pos(map, x_pos, y_pos, position);
        lower_tile_at_pos(map, -x_pos, y_pos, position);
        lower_tile_at_pos(map, x_pos, -y_pos, position);
        lower_tile_at_pos(map, -x_pos, -y_pos, position);
    }
}

static void lower_nearby_tiles(tilemap_t *map, int range)
{
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            bomb_check_loop(map, i, j, range);
        }
    }
}

void bomb_tile(tilemap_t *map)
{
    int *tile_map = map->heights;
    size_t clicked_pos = map->clicked_x + map->clicked_y * map->width;

    if (map->clicked_x == -1 || map->clicked_y == -1
        || tile_map[clicked_pos] - BOMB_RANGE < 0)
        return;
    for (int i = 0; i <= BOMB_RANGE; i++) {
        lower_nearby_tiles(map, i);
    }
    tilemap_calculate_vertices(map);
}
