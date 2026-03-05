/*
** EPITECH PROJECT, 2026
** tilemap_destroy.c
** File description:
** Free the tilemap
*/

#include <SFML/Graphics/VertexArray.h>
#include <SFML/Graphics/View.h>
#include <stdlib.h>

#include "tilemap.h"

void tilemap_destroy(tilemap_t *tilemap)
{
    if (!tilemap)
        return;
    free(tilemap->heights);
    free(tilemap->types);
    if (tilemap->vertices)
        sfVertexArray_destroy(tilemap->vertices);
    if (tilemap->hover_vertices)
        sfVertexArray_destroy(tilemap->hover_vertices);
    if (tilemap->selected_vertices)
        sfVertexArray_destroy(tilemap->selected_vertices);
    if (tilemap->view)
        sfView_destroy(tilemap->view);
    free(tilemap);
}
