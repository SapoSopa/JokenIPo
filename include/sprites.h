#pragma once

#include <tmx.h>
#include <raylib.h>

#define LINE_THICKNESS 2.5

void *raylib_tex_loader(const char *path);

void raylib_free_tex(void *tex);

Color int_to_color(int color);

void draw_polyline(double offset_x, double offset_y, double **points, int points_count, Color color);

void draw_polygon(double offset_x, double offset_y, double **points, int points_count, Color color);

void draw_objects(tmx_object_group *objgr);

void draw_image_layer(tmx_image *image);

void draw_tile(void *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
               unsigned int dx, unsigned int dy, float opacity, unsigned int flags);

void draw_layer(tmx_map *map, tmx_layer *layer);

void draw_all_layers(tmx_map *map, tmx_layer *layers);

void render_map(tmx_map *map);