#include "jgl.h"

namespace jgl
{
	Triangle3D		calc_face_triangle(const Face* face, const jgl::Matrix4x4 rot_matrix, const Mesh_part* mesh_part, const Vector3 delta)
	{
		Triangle3D	result;

		result.a = (rot_matrix * mesh_part->vertices(face->index_vertices[0])) + delta;
		result.b = (rot_matrix * mesh_part->vertices(face->index_vertices[1])) + delta;
		result.c = (rot_matrix * mesh_part->vertices(face->index_vertices[2])) + delta;
		return (result);
	}

	Vector3		triangle_center(const Triangle3D tri)
	{
		Vector3	ret;

		ret = Vector3(
			(tri.a.x + tri.b.x + tri.c.x) / 3.0f,
			(tri.a.y + tri.b.y + tri.c.y) / 3.0f,
			(tri.a.z + tri.b.z + tri.c.z) / 3.0f
		);
		return (ret);
	}

	float signed_volume(const jgl::Vector3 a, const jgl::Vector3 b, const jgl::Vector3 c, const jgl::Vector3 d)
	{
		return (((b - a).cross(c - a)).dot(d - a) / 6);
	}

#define POSITIVE 1
#define NEGATIVE 0

	int get_sign(const float value)
	{
		if (value >= 0)
			return (POSITIVE);
		return (NEGATIVE);
	}

	bool		intersect_triangle_by_segment(const Triangle3D triangle, const Line3D line)
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

	bool triangles_intersection(const Triangle3D tri1, const Triangle3D tri2)
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

	bool triangles_line_intersection(const Line3D line, const Triangle3D tri, Vector3* intersection)
	{
		Vector3 end = line.a + line.b * 1000;
		int s1 = get_sign(signed_volume(line.a, tri.a, tri.b, tri.c));
		int s2 = get_sign(signed_volume(end, tri.a, tri.b, tri.c));

		if (s1 != s2)
		{
			int s3 = get_sign(signed_volume(line.a, end, tri.a, tri.b));
			int s4 = get_sign(signed_volume(line.a, end, tri.b, tri.c));
			int s5 = get_sign(signed_volume(line.a, end, tri.c, tri.a));
			if (s3 == s4 && s4 == s5)
			{
				Vector3 n = (tri.b - tri.a).cross(tri.c - tri.a);
				float t = -(line.a).dot(n - tri.a) / (line.a).dot(end - line.a);
				*intersection = (line.a + (end - line.a) * t);
				return true;
			}

		}
		*intersection = Vector3();
		return false;
	}

	bool is_triangle_parallele(const Triangle3D tri1, const Triangle3D tri2)
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

	bool compare_faces(const Face* face, const Mesh* base, const Mesh_part *base_part, const Mesh* to_check)
	{
		Triangle3D	tri_comp;
		Triangle3D	tri_tar;
		Face* actual;
		float		dist;

		tri_tar = calc_face_triangle(face, base->rot_matrix(), base_part, base->pos() + base->velocity());
		dist = abs(to_check->pos().distance(triangle_center(tri_tar)));
		if (dist < abs(tri_tar.a.distance(tri_tar.b)) ||
			dist < abs(tri_tar.a.distance(tri_tar.c)) ||
			dist < abs(tri_tar.c.distance(tri_tar.b)))
		{
			for (uint32_t tmp_index = 0; tmp_index < to_check->parts().size(); tmp_index++)
			{
				Mesh_part* tmp = to_check->control_part(tmp_index);
				for (uint32_t i = 0; i < tmp->faces().size(); i++)
				{
					actual = tmp->faces(i);
					tri_comp = calc_face_triangle(actual, to_check->rot_matrix(), tmp, to_check->pos() + to_check->velocity());
					if (triangles_intersection(tri_comp, tri_tar) == true)
						return (true);
				}
			}
		}
		return (false);
	}

	bool intersect_mesh_ray(Vector3 pos, Vector3 direction, Mesh* to_check, Vector3* intersection)
	{
		Face* tmp;

		for (uint32_t tmp_index = 0; tmp_index < to_check->parts().size(); tmp_index++)
		{
			Mesh_part* tmp_part = to_check->control_part(tmp_index);
			for (uint32_t i = 0; i < tmp_part->faces().size(); i++)
			{
				tmp = tmp_part->faces(i);
				if (triangles_line_intersection(Line3D(pos, direction),
					calc_face_triangle(tmp, to_check->rot_matrix(), tmp_part, to_check->pos()), intersection) == true)
					return (true);
			}
		}
		return (false);
	}

	bool intersect_mesh(const Mesh* to_move, const Mesh* to_check)
	{
		Face* tmp;
		for (uint32_t tmp_index = 0; tmp_index < to_check->parts().size(); tmp_index++)
		{
			Mesh_part* tmp_part = to_check->control_part(tmp_index);
			for (uint32_t i = 0; i < tmp_part->faces().size(); i++)
			{
				tmp = tmp_part->faces(i);
				if (compare_faces(tmp, to_check, tmp_part, to_move) == true)
					return (true);
			}
		}
		return (false);
	}

	bool intersect_bubble_box(const Mesh* to_move, const Mesh* to_check)
	{
		Vector3 move_center;
		Vector3 check_center;
		float distance;

		move_center = to_move->pos() + to_move->center();
		check_center = to_check->pos() + to_check->center();
		distance = move_center.distance(check_center);
		if (distance < to_move->radius() + to_check->radius())
		{
			return (true);
		}
		return (false);
	}
}