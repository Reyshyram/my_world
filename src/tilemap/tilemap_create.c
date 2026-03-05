/*
** EPITECH PROJECT, 2026
** tilemap_create.c
** File description:
** Create the tilemap
*/

#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Graphics/View.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/engine.h"

#include "tilemap.h"

void init_tile_data(tilemap_t *tilemap, size_t nb_tiles)
{
    int random_low = rand() % 3;

    for (size_t i = 0; i < nb_tiles; i++) {
        tilemap->heights[i] = MAX_HEIGHT / 8 + rand() % 8 - 4;
        tilemap->types[i] = TILE_TYPE_GRASS;
    }
    for (size_t i = 0; i < nb_tiles; i++) {
        if (random_low == 1 && i % tilemap->width < tilemap->width / 2
            && i < tilemap->height * tilemap->width / 2) {
            tilemap->heights[i] = MAX_HEIGHT / 2 + rand() % 4 - 1;
            tilemap->types[i] = get_tile_type(tilemap->heights[i]);
        }
        if (random_low == 2) {
            tilemap->heights[i] = MAX_HEIGHT / 4 + rand() % 6 - 2;
            tilemap->types[i] = get_tile_type(tilemap->heights[i]);
        }
    }
}

static bool tilemap_initialize(tilemap_t *tilemap, sfVector2u *window_size)
{
    size_t nb_tiles = tilemap->width * tilemap->height;

    tilemap->heights = malloc(sizeof(int) * nb_tiles);
    tilemap->types = malloc(sizeof(tile_type_t) * nb_tiles);
    tilemap->vertices = sfVertexArray_create();
    tilemap->hover_vertices = sfVertexArray_create();
    tilemap->view = sfView_create();
    if (!tilemap->heights || !tilemap->types || !tilemap->vertices
        || !tilemap->view || !tilemap->hover_vertices)
        return false;
    init_tile_data(tilemap, nb_tiles);
    sfVertexArray_setPrimitiveType(tilemap->vertices, sfQuads);
    sfVertexArray_setPrimitiveType(tilemap->hover_vertices, sfQuads);
    sfView_setSize(tilemap->view, TOV2F(*window_size));
    sfView_setCenter(tilemap->view,
        (sfVector2f) {0.0F, -(float) MAX_HEIGHT * TILE_HEIGHT / 2.0F});
    return true;
}

tilemap_t *tilemap_create(size_t width, size_t height, sfVector2u *window_size)
{
    tilemap_t *tilemap = malloc(sizeof(*tilemap));

    if (!tilemap)
        return nullptr;
    memset(tilemap, 0, sizeof(*tilemap));
    tilemap->width = width;
    tilemap->height = height;
    if (!tilemap_initialize(tilemap, window_size)) {
        tilemap_destroy(tilemap);
        return nullptr;
    }
    randomize_tile_map(tilemap);
    tilemap_calculate_vertices(tilemap);
    tilemap->clicked_x = -1;
    tilemap->clicked_y = -1;
    return tilemap;
}
