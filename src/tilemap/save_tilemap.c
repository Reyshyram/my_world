/*
** EPITECH PROJECT, 2026
** save_tilemap.c
** File description:
** Save the tilemap
*/

#include <SFML/Audio/Sound.h>
#include <stdio.h>

#include "graphics/resources.h"

#include "my_world.h"
#include "simulation.h"
#include "tilemap.h"

void save_tilemap(simulation_data_t *data)
{
    FILE *f = fopen(data->filename, "w");
    size_t curr_index = 0;

    if (!f)
        return;
    fprintf(f, "%zu %zu\n", data->tilemap->height, data->tilemap->width);
    for (size_t y = 0; y < data->tilemap->height; y++) {
        for (size_t x = 0; x < data->tilemap->width; x++) {
            curr_index = y * data->tilemap->width + x;
            fprintf(f, "%d,%d%s", data->tilemap->heights[curr_index],
                data->tilemap->types[curr_index],
                x != data->tilemap->width - 1 ? " " : "");
        }
        fprintf(f, "\n");
    }
    fclose(f);
    sfSound_play(resources_load_sound(data->tilemap->resources, SAVE_SOUND));
}
