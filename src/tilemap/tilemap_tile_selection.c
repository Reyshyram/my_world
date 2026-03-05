/*
** EPITECH PROJECT, 2026
** tilemap_tile_selection
** File description:
** selects the hovered tile
*/

#include <SFML/Graphics/Vertex.h>
#include <SFML/Graphics/VertexArray.h>
#include <stddef.h>

#include "tilemap.h"

void update_selected_vertices(tilemap_t *map)
{
    sfVertex vertex = {.color = SELECTED_COLOR};
    int height = 0;

    sfVertexArray_clear(map->selected_vertices);
    if (map->clicked_x == -1 || map->clicked_y == -1)
        return;
    height = map->heights[map->clicked_y * map->width + map->clicked_x];
    for (size_t i = 0; i < 4; i++) {
        vertex.position =
            project_point(map, map->clicked_x + CORNERS_OFFSETS[i].x,
            map->clicked_y + CORNERS_OFFSETS[i].y, height);
        sfVertexArray_append(map->selected_vertices, vertex);
    }
    vertex.position = project_point(map, map->clicked_x + CORNERS_OFFSETS[0].x,
        map->clicked_y + CORNERS_OFFSETS[0].y, height);
    sfVertexArray_append(map->selected_vertices, vertex);
}

void select_hovered_tile(tilemap_t *map)
{
    if (!map->is_tile_hovered)
        return;
    map->clicked_x = (int) map->hover_x;
    map->clicked_y = (int) map->hover_y;
    update_selected_vertices(map);
}
