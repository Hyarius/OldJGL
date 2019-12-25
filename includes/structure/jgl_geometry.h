#ifndef JGL_GEOMETRY_H
#define JGL_GEOMETRY_H

using namespace std;

struct	Poly_side
{
	size_t index_vertices[2];
	Vector2	normale;

	Poly_side(size_t p_index1, size_t p_index2, Vector2 p_normale)
	{
		index_vertices[0] = p_index1;
		index_vertices[1] = p_index2;
		normale = p_normale;
	}
};

class Polygon2D
{
private:
	Vector2 _pos;

	vector<Vector2> _points;
	vector<Poly_side> _sides;

public:
	Polygon2D(Vector2 p_pos = 0);

	void draw(Color p_color, c_viewport *viewport = nullptr, float scale = 1.0f, int width = 1);

	bool contact(Polygon2D &other, float scale = 1);
	bool is_pointed(Vector2 point, float scale = 1);

	void add_point(Vector2 p_point){_points.push_back(p_point);}
	void remove_point(size_t index){if (index < _points.size())_points.erase(_points.begin() + index);}

	void add_side(Poly_side p_side){_sides.push_back(p_side);}
	void add_side(size_t index1, size_t index2);
	void remove_side(size_t index){if (index < _sides.size())_sides.erase(_sides.begin() + index);}

	void set_pos(Vector2 p_pos){_pos = p_pos;}

	Vector2 pos(){return (_pos);}
	vector<Vector2> &points(){return (_points);}
	vector<Poly_side> &sides(){return (_sides);}
};

#endif
