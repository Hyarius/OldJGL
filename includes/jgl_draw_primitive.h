#ifndef JGL_DRAW_PRIMITIVE_H
#define JGL_DRAW_PRIMITIVE_H

#include "jgl_includes.h"
#include "jgl_vector.h"
#include "jgl_color.h"
#include "jgl_system.h"

namespace jgl
{
	void draw_pixel_color(const Vector3 points, const Color colors, const size_t nb = 1);
	void draw_line_color(const Vector3* points, const Color* colors, const size_t nb = 1);
	void draw_triangle_color(const Vector3* points, const Color* colors, const size_t nb = 1);
	void draw_triangle_texture(const Vector3* points, const Vector2* uvs, float alpha, const size_t nb = 1);
	void fill_triangle_color(const Vector3* points, const Color* colors, const size_t nb = 1);

	jgl::Array<Vector2> calc_point(const size_t width);
	void draw_line(const Vector2 p1, const Vector2 p2, const size_t width, const Color p_color, const Viewport* viewport = nullptr);
	void draw_point(const Vector2 center, const size_t width, const Color p_color, const Viewport* viewport = nullptr);
	void draw_rectangle(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr, const size_t width, const Color p_color, const Viewport* viewport = nullptr);
	void fill_rectangle(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr, const Color p_color, const Viewport* viewport = nullptr);
	void draw_rectangle(const Vector2 pos, const Vector2 size, const size_t width, const Color p_color, const Viewport* viewport = nullptr);
	void fill_rectangle(const Vector2 pos, const Vector2 size, const Color p_color, const Viewport* viewport = nullptr);
	void fill_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const Color p_color, const Viewport* viewport = nullptr);
	void draw_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const size_t width, const Color p_color, const Viewport* viewport = nullptr);
}
#endif
