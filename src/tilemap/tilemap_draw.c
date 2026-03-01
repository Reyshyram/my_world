/*
** EPITECH PROJECT, 2026
** tilemap_draw.c
** File description:
** Show the tilemap
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>

#include "tilemap.h"

void tilemap_draw(const tilemap_t *map, sfRenderWindow *window)
{
    if (!map || !map->vertices || !map->view)
        return;
    sfRenderWindow_setView(window, map->view);
    sfRenderWindow_drawVertexArray(window, map->vertices, nullptr);
    sfRenderWindow_setView(window, sfRenderWindow_getDefaultView(window));
}
