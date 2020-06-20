#ifndef JGL_GEOMETRY_H
#define JGL_GEOMETRY_H

#include "jgl_vector.h"

namespace jgl
{
	struct Uv
	{
		float u;
		float v;

		Uv(float p_u = 0.0f, float p_v = 0.0f) : u(p_u), v(p_v) {}
		Uv(Vector2 pos) : u(pos.x), v(pos.y) {}
	};

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

	struct Pixel
	{
		float x;
		float y;
		float z;

		Pixel(int p_value);
		Pixel(Vector2 p_value);
		Pixel(float p_value = -1);
		Pixel(float p_x, float p_y, float p_z = -1);
		Pixel(int p_x, int p_y, int p_z = -1);

		Pixel& operator = (Vector2 p_value);

		Pixel operator + (const Pixel& delta);
		Pixel operator - (const Pixel& delta);
		Pixel operator * (const Pixel& delta);
		Pixel operator / (const Pixel& delta);
		void operator += (const Pixel& delta);
		void operator -= (const Pixel& delta);
		void operator *= (const Pixel& delta);
		void operator /= (const Pixel& delta);
		bool operator == (const Pixel& delta) const;
		bool operator != (const Pixel& delta) const;
		bool operator < (const Pixel& other) const;
		bool operator > (const Pixel& other) const;
		float* decompose();
		float distance(Pixel& point);
		Pixel normalize();
		Pixel cross(Pixel& other);
		float dot(Pixel& other);
		jgl::Unique_string str();
		Pixel floor();
	};
}

std::ostream& operator<<(std::ostream& os, jgl::Line3D& value);
std::ostream& operator<<(std::ostream& os, jgl::Triangle3D& value);
std::ostream& operator<<(std::ostream& os, jgl::Pixel& value);


#endif
