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
        while (height[i] < MIN_HEIGHT + 3)
            height[i] += rand() % 2;
        while (height[i] > MAX_HEIGHT)
            height[i] += rand() % 6 - 10;
    }
}

void randomize_tile_map(tilemap_t *map)
{
    int *height_map = map->heights;

    for (size_t i = 0; i < map->width * map->height; i++) {
        if (i < map->width && i != 0)
            height_map[i] += height_map[i - 1] + rand() % 2 - 1;
        if (i % map->width == 0 && i > map->width)
            height_map[i] += height_map[i - map->width] + rand() % 2 - 1;
        if (i % map->width != 0 && i > map->width)
            height_map[i] +=
                (height_map[i - 1] + height_map[i - map->width]) / 2
                + (rand() % 2) - 1;
        if (height_map[i] > MAX_HEIGHT)
            height_map[i] -= rand() % MAX_HEIGHT / 64;
        if (height_map[i] < MIN_HEIGHT)
            height_map[i] -= rand() % MAX_HEIGHT / 4;
    }
    resolve_height_issues(map);
    for (size_t i = 0; i < map->width * map->height; i++)
        map->types[i] = get_tile_type(height_map[i]);

}
