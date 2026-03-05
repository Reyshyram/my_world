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
    map->heights[position] -= (int) map->tool_strength;
    if (map->heights[position] <= MIN_HEIGHT)
        map->heights[position] = MIN_HEIGHT;
    tilemap_calculate_vertices(map);
}

void raise_tile_height(tilemap_t *map)
{
    size_t position = map->clicked_x + map->clicked_y * map->width;

    if (map->clicked_x == -1 || map->clicked_y == -1)
        return;
    map->heights[position] += (int) map->tool_strength;
    if (map->heights[position] >= MAX_HEIGHT)
        map->heights[position] = MAX_HEIGHT;
    tilemap_calculate_vertices(map);
}

void increase_tool_strength(tilemap_t *map)
{
    if (map->tool_strength < MAX_TOOL_STRENGTH)
        map->tool_strength++;
}

void decrease_tool_strength(tilemap_t *map)
{
    if (map->tool_strength > MIN_TOOL_STRENGTH)
        map->tool_strength--;
}
