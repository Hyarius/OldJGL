#include "jgl.h"

Triangle3D		calc_face_triangle(Face *face, c_mesh *mesh)
{
	Triangle3D	result;

	result.a = (mesh->rot_matrix() * mesh->vertices()[face->index_vertices[0]]) + mesh->pos() + mesh->velocity();
	result.b = (mesh->rot_matrix() * mesh->vertices()[face->index_vertices[1]]) + mesh->pos() + mesh->velocity();
	result.c = (mesh->rot_matrix() * mesh->vertices()[face->index_vertices[2]]) + mesh->pos() + mesh->velocity();
	return (result);
}

Vector3		triangle_center(Triangle3D tri)
{
	Vector3	ret;

	ret = Vector3(
		(tri.a.x + tri.b.x + tri.c.x) / 3.0f,
		(tri.a.y + tri.b.y + tri.c.y) / 3.0f,
		(tri.a.z + tri.b.z + tri.c.z) / 3.0f
	);
	return (ret);
}

float signed_volume(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
	return (((b - a).cross(c - a)).dot(d - a) / 6);
}

#define POSITIVE 1
#define NEGATIVE 0

int get_sign(float value)
{
	if (value >= 0)
		return (POSITIVE);
	return (NEGATIVE);
}

bool		intersect_triangle_by_segment(Triangle3D triangle, Line3D line)
{
	int a = get_sign(signed_volume(line.a, triangle.a, triangle.b, triangle.c));
	int b = get_sign(signed_volume(line.b, triangle.a, triangle.b, triangle.c));
	int c = get_sign(signed_volume(line.a, line.b, triangle.a, triangle.b));
	int d = get_sign(signed_volume(line.a, line.b, triangle.b, triangle.c));
	int e = get_sign(signed_volume(line.a, line.b, triangle.c, triangle.a));

	if (a != b && c == d && d == e)
		return (true);
	return (false);
}

bool triangles_intersection(Triangle3D tri1, Triangle3D tri2)
{
	Line3D	seg;

	seg = Line3D(tri1.a, tri1.b);
	if (intersect_triangle_by_segment(tri2, seg) == true)
		return (true);
	seg = Line3D(tri1.b, tri1.c);
	if (intersect_triangle_by_segment(tri2, seg) == true)
		return (true);
	seg = Line3D(tri1.a, tri1.c);
	if (intersect_triangle_by_segment(tri2, seg) == true)
		return (true);
	return (false);
}

bool is_triangle_parallele(Triangle3D tri1, Triangle3D tri2)
{
	Vector3 normale_a;
	Vector3 normale_b;
	Vector3 b;
	Vector3 c;
	float tmp;

	b = tri1.b - tri1.a;
	c = tri1.c - tri1.a;
	normale_a = b.cross(c).normalize();
	b = tri2.b - tri2.a;
	c = tri2.c - tri2.a;
	normale_b = b.cross(c).normalize();
	tmp = normale_a.dot(normale_b);
	if (tmp == 1 || tmp == -1)
		return (true);
	return (false);
}

bool compare_faces(Face *face, c_mesh *to_move, c_mesh *to_check)
{
	Triangle3D	tri_comp;
	Triangle3D	tri_tar;
	Face		*actual;
	float		dist;

	tri_tar = calc_face_triangle(face, to_move);
	dist = abs(to_check->pos().distance(triangle_center(tri_tar)));
	if (dist < abs(tri_tar.a.distance(tri_tar.b)) ||
		dist < abs(tri_tar.a.distance(tri_tar.c)) ||
		dist < abs(tri_tar.c.distance(tri_tar.b)))
	{
		for (size_t i = 0; i < to_check->faces().size(); i++)
		{
			actual = to_check->faces(i);
			tri_comp = calc_face_triangle(actual, to_check);
			if (triangles_intersection(tri_comp, tri_tar) == true)
				return (true);
		}
	}
	return (false);
}

bool intersect_mesh(c_mesh *to_move, c_mesh *to_check)
{
	Face *tmp;

	for (size_t i = 0; i < to_check->faces().size(); i++)
	{
		tmp = to_check->faces(i);
		if (compare_faces(tmp, to_check, to_move) == true)
			return (true);
	}
	return (false);
}

bool intersect_bubble_box(c_mesh *to_move, c_mesh *to_check)
{
	Vector3 move_center;
	Vector3 check_center;
	float distance;

	move_center = to_move->pos() + to_move->center();
	check_center = to_check->pos() + to_check->center();
	distance = move_center.distance(check_center);
	if (distance < to_move->radius() + to_check->radius())
	{
		cout << "From " << move_center << " to " << check_center << " = " << distance << " vs " << ftoa(to_move->radius() + to_check->radius(), 2) << endl;
		return (true);
	}
	return (false);
}
