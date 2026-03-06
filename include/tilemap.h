/*
** EPITECH PROJECT, 2026
** tilemap.h
** File description:
** Tilemap
*/

#ifndef TILEMAP_H_
// clang-format off
    #define TILEMAP_H_

    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>
    #include <stdint.h>

    #define TILE_H_WIDTH 24
    #define TILE_H_LENGTH 12
    #define TILE_HEIGHT 24
    #define MAP_DEFAULT_W 128
    #define MAP_DEFAULT_H 128
    #define MIN_HEIGHT 1
    #define MAX_HEIGHT 64

    #define X_AXIS_DARKEN 0.5
    #define Y_AXIS_DARKEN 0.7

    #define CAMERA_SPEED 500
    #define ROTATION_SPEED 1
    #define ZOOM_SPEED 0.5F

    #define BOMB_RANGE 10
    #define MIN_TOOL_STRENGTH 1
    #define MAX_TOOL_STRENGTH 32
// clang-format on

typedef enum tile_type {
    TILE_TYPE_GRASS,
    TILE_TYPE_DIRT,
    TILE_TYPE_ROCK,
    TILE_TYPE_SAND,
    TILE_TYPE_COUNT,
} tile_type_t;

typedef enum {
    CORNER_TOP_LEFT = 0,
    CORNER_TOP_RIGHT = 1,
    CORNER_BOTTOM_RIGHT = 2,
    CORNER_BOTTOM_LEFT = 3,
} corner_t;

static const sfVector2u CORNERS_OFFSETS[4] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1},
};

static const sfColor TILE_COLORS[TILE_TYPE_COUNT] = {
    [TILE_TYPE_GRASS] = {75, 128, 61, 255},
    [TILE_TYPE_DIRT] = {132, 95, 66, 255},
    [TILE_TYPE_ROCK] = {124, 124, 124, 255},
    [TILE_TYPE_SAND] = {219, 207, 163, 255},
};

typedef struct tilemap {
    size_t width;
    size_t height;
    int *heights;
    tile_type_t *types;
    sfVertexArray *vertices;
    sfVertexArray *hover_vertices;
    sfVertexArray *selected_vertices;
    sfView *view;
    float rotation_rad;
    bool is_tile_hovered;
    size_t hover_x;
    size_t hover_y;
    int clicked_x;
    int clicked_y;
    size_t tool_strength;
} tilemap_t;

static const sfColor HOVER_COLOR = {255, 255, 255, 80};
static const sfColor SELECTED_COLOR = {255, 80, 10, 255};

typedef struct {
    sfVertexArray *vertices;
    int tile_height;
    int neighbor_height;
    tile_type_t tile_type;
    sfVector2f corners[4];
} tile_render_t;

typedef struct {
    size_t x;
    size_t y;
    float order;
} draw_order_t;

tilemap_t *tilemap_create(size_t width, size_t height,
    sfVector2u *window_size);
void tilemap_destroy(tilemap_t *tilemap);
void init_tile_data(tilemap_t *tilemap, size_t nb_tiles);

draw_order_t *get_draw_order(const tilemap_t *tilemap,
    const sfVector2f *view_dir);
sfVector2f project_point(const tilemap_t *tilemap, size_t x, size_t y,
    size_t z);
void add_tile_side(sfVertexArray *vertex_array, const sfVector2f corners[4],
    const sfColor *color);
void add_visible_walls(const tilemap_t *tilemap, tile_render_t *tile_render,
    const draw_order_t *tile, const sfVector2f *view_dir);
void tilemap_calculate_vertices(tilemap_t *tilemap);

void tilemap_draw(const tilemap_t *tilemap, sfRenderWindow *window);
void randomize_tile_map(tilemap_t *map);
tile_type_t get_tile_type(int height);
void tilemap_update_hover(tilemap_t *tilemap, sfRenderWindow *window);
void lower_tile_height(tilemap_t *map);
void raise_tile_height(tilemap_t *map);
void increase_tool_strength(tilemap_t *map);
void decrease_tool_strength(tilemap_t *map);
void select_hovered_tile(tilemap_t *map);
void update_selected_vertices(tilemap_t *map);
void change_tile_type(tilemap_t *map);
int check_amount_tiles_nearby(size_t pos, tilemap_t *map);
void bomb_tile(tilemap_t *map);

void save_tilemap(tilemap_t *map, char *filename);

#endif /* !TILEMAP_H_ */
