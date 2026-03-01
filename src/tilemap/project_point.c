/*
** EPITECH PROJECT, 2026
** project_point.c
** File description:
** Project point
*/

#include <SFML/System/Vector2.h>
#include <math.h>
#include <stddef.h>

#include "tilemap.h"

// First, rotate the coords around the map center
// Then, apply the isometric projection
sfVector2f project_point(const tilemap_t *tilemap, size_t x, size_t y,
    size_t z)
{
    float center_x = (float) x - (float) tilemap->width / 2;
    float center_y = (float) y - (float) tilemap->height / 2;
    float cos_rot = cosf(tilemap->rotation_rad);
    float sin_rot = sinf(tilemap->rotation_rad);
    float point_x = center_x * cos_rot - center_y * sin_rot;
    float point_y = center_x * sin_rot + center_y * cos_rot;

    return (sfVector2f) {
        (point_x - point_y) * TILE_H_WIDTH,
        (point_x + point_y) * TILE_H_LENGTH - (float) z * TILE_HEIGHT,
    };
}
