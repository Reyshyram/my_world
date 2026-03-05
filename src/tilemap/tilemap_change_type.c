/*
** EPITECH PROJECT, 2026
** tilemap_change_type.c
** File description:
** Change the tile type
*/

#include <stddef.h>

#include "tilemap.h"

void change_tile_type(tilemap_t *map)
{
    size_t position = map->clicked_x + map->clicked_y * map->width;

    if (map->clicked_x == -1 || map->clicked_y == -1)
        return;
    map->types[position] = (map->types[position] + 1) % TILE_TYPE_COUNT;
    tilemap_calculate_vertices(map);
}
