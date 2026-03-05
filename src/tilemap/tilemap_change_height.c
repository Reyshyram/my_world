/*
** EPITECH PROJECT, 2026
** tilemap_change_height
** File description:
** hold the functions for both buttons up and down
*/

#include <stddef.h>

#include "tilemap.h"

void lower_tile_height(tilemap_t *map)
{
    size_t position = map->clicked_x + map->clicked_y * map->width;

    if (map->clicked_x == -1 || map->clicked_y == -1)
        return;
    if (map->heights[position] <= MIN_HEIGHT)
        return;
    map->heights[position] -= 1;
    tilemap_calculate_vertices(map);
}

void raise_tile_height(tilemap_t *map)
{
    size_t position = map->clicked_x + map->clicked_y * map->width;

    if (map->clicked_x == -1 || map->clicked_y == -1)
        return;
    if (map->heights[position] >= MAX_HEIGHT)
        return;
    map->heights[position] += 1;
    tilemap_calculate_vertices(map);
}
