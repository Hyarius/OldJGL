#ifndef JGL_DRAW_PRIMITIVE_H
#define JGL_DRAW_PRIMITIVE_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

using namespace std;

void draw_pixel_color(Pixel points, Color colors, size_t nb = 1);
void draw_pixel_color(Pixel *points, Color *colors, size_t nb = 1);
void draw_line_color(Pixel *points, Color *colors, size_t nb = 1);
void draw_triangle_color(Pixel *points, Color *colors, size_t nb = 1);
void draw_triangle_texture(Pixel *points, Uv *uvs, float alpha, size_t nb = 1);
void fill_triangle_color(Pixel *points, Color *colors, size_t nb = 1);

vector<Vector2> calc_point(int width);
void draw_line(Vector2 p1, Vector2 p2, size_t width, Color p_color, c_viewport *viewport = nullptr);
void draw_point(Vector2 center, size_t width, Color p_color, c_viewport *viewport = nullptr);
void draw_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, c_viewport *viewport = nullptr);
void fill_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, c_viewport *viewport = nullptr);
void draw_rectangle(Vector2 pos, Vector2 size, Color p_color, c_viewport *viewport = nullptr);
void fill_rectangle(Vector2 pos, Vector2 size, Color p_color, c_viewport *viewport = nullptr);
void fill_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, c_viewport *viewport = nullptr);
void draw_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, c_viewport *viewport = nullptr);

#endif
