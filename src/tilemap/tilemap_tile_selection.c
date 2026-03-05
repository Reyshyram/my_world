/*
** EPITECH PROJECT, 2026
** tilemap_tile_selection
** File description:
** selects the hovered tile
*/

#include "tilemap.h"

void select_hovered_tile(tilemap_t *map)
{
    map->clicked_x = map->hover_x;
    map->clicked_y = map->hover_y;
}
