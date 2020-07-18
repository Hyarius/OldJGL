#include "jgl.h"

namespace jgl
{
	std::vector<Vector2> calc_point(const size_t width)
	{
		std::vector<Vector2> result;
		Vector2 center = 0;
		Vector2 actual;

		for (actual.x = -static_cast<int>(width) / 2.0f; actual.x <= static_cast<int>(width) / 2.0f || actual.x == 0; actual.x++)
		{
			for (actual.y = -static_cast<int>(width) / 2.0f; actual.y <= static_cast<int>(width) / 2.0f || actual.y == 0; actual.y++)
			{
				if (center.distance(actual) < width / 2.0f)
					result.push_back(actual);
			}
		}

		return (result);
	}

	void draw_line(const Vector2 p1, const Vector2 p2, const size_t width, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		std::vector<Vector2> to_draw = calc_point(width);
		Vector2 actual;
		Color colors[2];
		Vector3 Vector3s[2];

		colors[0] = p_color;
		colors[1] = p_color;
		for (size_t i = 0; i < to_draw.size(); i++)
		{
			Vector3s[0] = convert_screen_to_opengl(Vector2(to_draw[i].x + p1.x, to_draw[i].y + p1.y));
			Vector3s[1] = convert_screen_to_opengl(Vector2(to_draw[i].x + p2.x, to_draw[i].y + p2.y));
			draw_line_color(Vector3s, colors, 1);
		}

	}

	void draw_point(const Vector2 center, const size_t width, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		Vector3 tmp_center = 0;
		Vector3 actual;

		for (actual.x = -static_cast<int>(width) / 2.0f; actual.x <= static_cast<int>(width) / 2.0f || actual.x == 0; actual.x++)
		{
			for (actual.y = -static_cast<int>(width) / 2.0f; actual.y <= static_cast<int>(width) / 2.0f || actual.y == 0; actual.y++)
			{
				if (tmp_center.distance(actual) < width / 2.0f)
					draw_pixel_color(Vector3(actual.x + center.x, actual.y + center.y, 0.0f), p_color);
			}
		}
	}

	void draw_rectangle(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		Vector3 points[] = {
			convert_screen_to_opengl(p_tl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_tr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_tl)
		};
		Color colors[] = {
			p_color,
			p_color,
			p_color,
			p_color,
			p_color,
			p_color
		};

		draw_triangle_color(points, colors, 2);
	}

	void fill_rectangle(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		Vector3 points[] = {
			convert_screen_to_opengl(p_tl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_tr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_tl)
		};
		Color colors[] = {
			p_color,
			p_color,
			p_color,
			p_color,
			p_color,
			p_color
		};

		fill_triangle_color(points, colors, 2);
	}

	void draw_rectangle(const Vector2 pos, const Vector2 size, const Color p_color, const Viewport* viewport)
	{
		draw_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, p_color, viewport);
	}

	void fill_rectangle(const Vector2 pos, const Vector2 size, const Color p_color, const Viewport* viewport)
	{
		fill_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, p_color, viewport);
	}

	void fill_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const Color p_color, const Viewport* viewport)
	{
		fill_rectangle(p_coord - p_size / 2, p_size, p_color, viewport);
	}

	void draw_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const Color p_color, const Viewport* viewport)
	{
		draw_rectangle(p_coord - p_size / 2, p_size, p_color, viewport);
	}
}