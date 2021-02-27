#include "jgl.h"

namespace jgl
{
	jgl::Array<Vector2> calc_point(const uint32_t width)
	{
		jgl::Array<Vector2> result;
		Vector2 center = width / 2;
		int tmp;

		if (width % 2 == 0)
			tmp = width + 1;
		else
			tmp = width;

		for (int i = 0; i < tmp; i++)
			for (int j = 0; j < tmp; j++)
			{
				Vector2 tmp_point = Vector2(i, j);
				if (width == 1 || (center.distance(tmp_point) <= width / 2.0f && center.distance(tmp_point) >= width / 2.05f))
					result.push_back(tmp_point - tmp / 2.0);
			}

		return (result);
	}

	jgl::Array<jgl::Array<Vector2>> circle_point;

	void draw_line(const Vector2 p1, const Vector2 p2, const uint32_t width, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		if (circle_point.size() <= width || circle_point[width].size() == 0)
		{
			if (circle_point.size() <= width)
				circle_point.resize(width + 1);
			circle_point[width] = calc_point(width);
		}
		jgl::Array<Vector2>& to_draw = circle_point[width];
		static jgl::Array<Vector3> points;

		points.clear();

		for (uint32_t i = 0; i < to_draw.size(); i++)
		{
			points.push_back(convert_screen_to_opengl(p1 + to_draw[i]));
			points.push_back(convert_screen_to_opengl(p2 + to_draw[i]));
		}
		draw_line_color(points.all(), p_color, points.size());
		
	}

	void draw_point(const Vector2 center, const uint32_t width, const Color p_color, const Viewport* viewport)
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

	void draw_rectangle(const Vector2 p_tl, const Vector2 p_tr, const Vector2 p_dl, const Vector2 p_dr, const uint32_t width, const Color p_color, const Viewport* viewport)
	{
		if (viewport != nullptr)
			viewport->use();

		Vector2 point_order[] = {
			p_tl, p_tr,
			p_tl, p_dl,
			p_dl, p_dr,
			p_tr, p_dr
		};

		if (circle_point.size() <= width || circle_point[width].size() == 0)
		{
			if (circle_point.size() <= width)
				circle_point.resize(width + 1);
			circle_point[width] = calc_point(width);
		}
		jgl::Array<Vector2>& to_draw = circle_point[width];
		static jgl::Array<Vector3> points;

		points.clear();

		for (uint32_t i = 0; i < to_draw.size(); i++)
		{
			for (uint32_t j = 0; j < 4; j++)
			{
				points.push_back(convert_screen_to_opengl(point_order[j * 2] + to_draw[i]));
				points.push_back(convert_screen_to_opengl(point_order[j * 2 + 1] + to_draw[i]));
			}
		}
		draw_line_color(points.all(), p_color, points.size());
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


		fill_triangle_color(points, p_color, 6);
	}

	void draw_rectangle(const Vector2 pos, const Vector2 size, const uint32_t width, const Color p_color, const Viewport* viewport)
	{
		draw_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, width, p_color, viewport);
	}

	void fill_rectangle(const Vector2 pos, const Vector2 size, const Color p_color, const Viewport* viewport)
	{
		fill_rectangle(pos, Vector2(pos.x + size.x, pos.y), Vector2(pos.x, pos.y + size.y), pos + size, p_color, viewport);
	}

	void fill_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const Color p_color, const Viewport* viewport)
	{
		fill_rectangle(p_coord - p_size / 2, p_size, p_color, viewport);
	}

	void draw_centred_rectangle(const Vector2 p_coord, const Vector2 p_size, const uint32_t width, const Color p_color, const Viewport* viewport)
	{
		draw_rectangle(p_coord - p_size / 2, p_size, width, p_color, viewport);
	}
}