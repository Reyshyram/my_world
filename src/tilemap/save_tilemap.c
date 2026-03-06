/*
** EPITECH PROJECT, 2026
** save_tilemap.c
** File description:
** Save the tilemap
*/

#include <stdio.h>

#include "tilemap.h"

void save_tilemap(tilemap_t *map, char *filename)
{
    FILE *f = fopen(filename, "w");
    size_t curr_index = 0;

    if (!f)
        return;
    fprintf(f, "%zu %zu\n", map->height, map->width);
    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            curr_index = y * map->width + x;
            fprintf(f, "%d,%d%s", map->heights[curr_index],
                map->types[curr_index], x != map->width - 1 ? " " : "");
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
