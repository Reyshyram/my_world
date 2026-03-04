/*
** EPITECH PROJECT, 2026
** tilemap_randomize_height
** File description:
** randomizes each tile's height
*/

#include "tilemap.h"
#include <stdlib.h>

tile_type_t get_tile_type(int height)
{
    if (height < MAX_HEIGHT / 4)
        return TILE_TYPE_SAND;
    if (height < (MAX_HEIGHT / 3))
        return TILE_TYPE_DIRT;
    if (height < (MAX_HEIGHT / 2))
        return TILE_TYPE_GRASS;
    return TILE_TYPE_ROCK;
}

static void resolve_height_issues(tilemap_t *map)
{
    int *height = map->heights;

    for (size_t i = 0; i < map->height * map->width; i++) {
        while (height[i] < MIN_HEIGHT)
            height[i] += rand() % MAX_HEIGHT / 16;
        while (height[i] > MAX_HEIGHT)
            height[i] -= rand() % MAX_HEIGHT / 16;
    }
}

static int resolve_single_tile_height(int height)
{
    while (height < MIN_HEIGHT)
        height += rand() % MAX_HEIGHT / 32;
    while (height > MAX_HEIGHT)
        height -= rand() % MAX_HEIGHT / 32;
    return height;
}

int check_amount_tiles_nearby(size_t pos, tilemap_t *map)
{
    int div = 0;

    if (pos > map->width)
        div += 1;
    if (pos < (map->height - 1) * map->width)
        div += 1;
    if (pos % map->width > 0)
        div += 1;
    if (pos % map->width < map->width)
        div += 1;
    return div;
}

int check_tile_height_availability(size_t pos, tilemap_t *map)
{
    int *height_map = map->heights;
    int number = 0;

    if (pos > map->width)
        number += height_map[pos - map->width];
    if (pos < (map->height - 1) * map->width)
        number += height_map[pos + map->width];
    if (pos % map->width > 0)
        number += height_map[pos - 1];
    if (pos % map->width < map->width)
        number += height_map[pos + 1];
    return number;
}

void randomize_tile_map(tilemap_t *map)
{
    int *height_map = map->heights;
    int number = 0;
    int div = 0;

    init_tile_data(map, map->height * map->width);
    for (size_t i = 0; i < map->width * map->height; i++) {
        number = check_tile_height_availability(i, map);
        div = check_amount_tiles_nearby(i, map);
        if (number / div < number / 4)
            div = 4;
        height_map[i] = number / div + rand() % 4 - 1;
        height_map[i] = resolve_single_tile_height(height_map[i]);
    }
    resolve_height_issues(map);
    for (size_t i = 0; i < map->width * map->height; i++)
        map->types[i] = get_tile_type(height_map[i]);
    tilemap_calculate_vertices(map);
}
