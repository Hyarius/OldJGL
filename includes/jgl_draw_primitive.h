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
void draw_triangle_texture(Pixel *points, Uv *uvs, float *alpha, size_t nb = 1);
void fill_triangle_color(Pixel *points, Color *colors, size_t nb = 1);

vector<Vector2> calc_point(int width);
void draw_line(Pixel p1, Pixel p2, int width, Color p_color, c_viewport *viewport = nullptr);
void draw_point(Pixel center, int width, Color p_color, c_viewport *viewport = nullptr);
void draw_rectangle(Pixel p_tl, Pixel p_tr, Pixel p_dl, Pixel p_dr, Color p_color, c_viewport *viewport = nullptr);
void fill_rectangle(Pixel p_tl, Pixel p_tr, Pixel p_dl, Pixel p_dr, Color p_color, c_viewport *viewport = nullptr);
void draw_rectangle(Pixel pos, Pixel size, Color p_color, c_viewport *viewport = nullptr);
void fill_rectangle(Pixel pos, Pixel size, Color p_color, c_viewport *viewport = nullptr);
void fill_centred_rectangle(Pixel p_coord, Pixel p_size, Color p_color, c_viewport *viewport = nullptr);
void draw_centred_rectangle(Pixel p_coord, Pixel p_size, Color p_color, c_viewport *viewport = nullptr);

#endif
