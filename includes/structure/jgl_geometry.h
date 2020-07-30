#ifndef JGL_GEOMETRY_H
#define JGL_GEOMETRY_H

#include "jgl_vector.h"

namespace jgl
{
	struct Rect
	{
		float x;
		float y;
		float w;
		float h;

		Rect() : x(0), y(0), w(1), h(1) {}
		Rect(float p_x, float p_y, float p_w, float p_h) : x(p_x), y(p_y), w(p_w), h(p_h) {}
		Rect(Vector2 pos, Vector2 size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
	};

	struct Line3D
	{
		Vector3 a;
		Vector3 b;

		Line3D(Vector3 p_a = 0, Vector3 p_b = 0) { a = p_a; b = p_b; }
	};

	struct Triangle3D
	{
		Vector3 a;
		Vector3 b;
		Vector3 c;

		Triangle3D(Vector3 p_a = 0, Vector3 p_b = 0, Vector3 p_c = 0) { a = p_a; b = p_b; c = p_c; }
	};
}


#endif
