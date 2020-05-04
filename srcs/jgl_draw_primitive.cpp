#include "jgl.h"

namespace jgl
{
	std::vector<Vector2> calc_point(size_t width)
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

	void draw_line(Vector2 p1, Vector2 p2, size_t width, Color p_color, Viewport* viewport)
	{
		if (viewport == nullptr)
			viewport = g_application->central_widget()->viewport();

		std::vector<Vector2> to_draw = calc_point(width);
		Vector2 actual;
		Color colors[2];
		Pixel pixels[2];

		colors[0] = p_color;
		colors[1] = p_color;
		for (size_t i = 0; i < to_draw.size(); i++)
		{
			pixels[0] = convert_screen_to_opengl(Vector2(to_draw[i].x + p1.x, to_draw[i].y + p1.y));
			pixels[1] = convert_screen_to_opengl(Vector2(to_draw[i].x + p2.x, to_draw[i].y + p2.y));
			draw_line_color(pixels, colors, 1);
		}

	}

	void draw_point(Vector2 center, size_t width, Color p_color, Viewport* viewport)
	{
		if (viewport == nullptr)
			viewport = g_application->central_widget()->viewport();

		Pixel tmp_center = 0;
		Pixel actual;

		for (actual.x = -static_cast<int>(width) / 2.0f; actual.x <= static_cast<int>(width) / 2.0f || actual.x == 0; actual.x++)
		{
			for (actual.y = -static_cast<int>(width) / 2.0f; actual.y <= static_cast<int>(width) / 2.0f || actual.y == 0; actual.y++)
			{
				if (tmp_center.distance(actual) < width / 2.0f)
					draw_pixel_color(Pixel(actual.x + center.x, actual.y + center.y), p_color);
			}
		}
	}

	void draw_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, Viewport* viewport)
	{
		if (viewport == nullptr)
			viewport = g_application->central_widget()->viewport();

		Pixel points[] = {
				convert_screen_to_opengl(p_tl),
				convert_screen_to_opengl(p_tr),
				convert_screen_to_opengl(p_dl),
				convert_screen_to_opengl(p_dr),
				convert_screen_to_opengl(p_dl),
				convert_screen_to_opengl(p_tr)
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

	void fill_rectangle(Vector2 p_tl, Vector2 p_tr, Vector2 p_dl, Vector2 p_dr, Color p_color, Viewport* viewport)
	{
		Pixel points[] = {
			convert_screen_to_opengl(p_tl),
			convert_screen_to_opengl(p_tr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_dr),
			convert_screen_to_opengl(p_dl),
			convert_screen_to_opengl(p_tr)
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

	void draw_rectangle(Vector2 pos, Vector2 size, Color p_color, Viewport* viewport)
	{
		draw_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, p_color, viewport);
	}

	void fill_rectangle(Vector2 pos, Vector2 size, Color p_color, Viewport* viewport)
	{
		fill_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, p_color, viewport);
	}

	void fill_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, Viewport* viewport)
	{
		fill_rectangle(p_coord - p_size / 2, p_size, p_color, viewport);
	}

	void draw_centred_rectangle(Vector2 p_coord, Vector2 p_size, Color p_color, Viewport* viewport)
	{
		draw_rectangle(p_coord - p_size / 2, p_size, p_color, viewport);
	}
}