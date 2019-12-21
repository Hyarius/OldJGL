#include "jgl.h"
#include "jgl_algorithm.h"

Polygon2D::Polygon2D(Vector2 p_pos)
{
	_pos = p_pos;
	_points.clear();
	_sides.clear();
}

void Polygon2D::draw(Color p_color, c_viewport *viewport, float scale, int width)
{
	for (size_t i = 0; i < _sides.size(); i++)
	{
		Vector2 pos1, pos2, center;

		pos1 = (_points[_sides[i].index_vertices[0]] * scale) + _pos;
		pos2 = (_points[_sides[i].index_vertices[1]] * scale) + _pos;

		draw_line(p_color, pos1, pos2, width, viewport);
	}
}

void Polygon2D::add_side(size_t index1, size_t index2)
{
	if (index1 >= _points.size() || index2 >= _points.size())
		return ;

	Vector2 normale;
	Vector2 base = (_points[index2] - _points[index1]).normalize();

	normale = (Vector2(0, 0)).cross(base);

	Poly_side poly = Poly_side(index1, index2, normale);

	_sides.push_back(poly);
}

bool Polygon2D::is_pointed(Vector2 point, float scale)
{
	vector<Vector2> tmp;

	for (size_t i = 0; i < _points.size(); i++)
		tmp.push_back((_points[i] * scale) + _pos);

	float value[3];

	for (size_t i = 0; i < this->_sides.size(); i++)
	{
		SAT_test(_sides[i].normale, tmp, &(value[0]), &(value[1]));
		SAT_test(_sides[i].normale, {point}, &(value[2]), &(value[2]));

		bool res1 = is_middle(value[0], value[2], value[1]);
		if (res1 == false)
			return (false);
	}

	return (true);
}
