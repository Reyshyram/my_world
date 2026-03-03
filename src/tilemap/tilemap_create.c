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

static bool tilemap_initialize(tilemap_t *tilemap, sfVector2u *window_size)
{
    size_t nb_tiles = tilemap->width * tilemap->height;

    tilemap->heights = malloc(sizeof(int) * nb_tiles);
    tilemap->types = malloc(sizeof(tile_type_t) * nb_tiles);
    tilemap->vertices = sfVertexArray_create();
    tilemap->view = sfView_create();
    if (!tilemap->heights || !tilemap->types || !tilemap->vertices
        || !tilemap->view)
        return false;
    for (size_t i = 0; i < nb_tiles; i++) {
        tilemap->heights[i] = MIN_HEIGHT;
        tilemap->types[i] = TILE_TYPE_GRASS;
    }
    sfVertexArray_setPrimitiveType(tilemap->vertices, sfQuads);
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
    randomize_tile_map(tilemap);
    tilemap_calculate_vertices(tilemap);
    return tilemap;
}
