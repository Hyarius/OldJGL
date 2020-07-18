#include "jgl.h"

namespace jgl
{
	Mesh* primitive_cube(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake)
	{
		Mesh* result;
		Vector3 delta = Vector3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

		result = new Mesh(pos);
		result->rotate(rot);

		result->add_point(Vector3(0.0f, 0.0f, 0.0f) - delta);
		result->add_point(Vector3(size.x, 0.0f, 0.0f) - delta);
		result->add_point(Vector3(size.x, 0.0f, size.z) - delta);
		result->add_point(Vector3(0.0f, 0.0f, size.z) - delta);
		result->add_point(Vector3(0.0f, size.y, 0.0f) - delta);
		result->add_point(Vector3(size.x, size.y, 0.0f) - delta);
		result->add_point(Vector3(size.x, size.y, size.z) - delta);
		result->add_point(Vector3(0.0f, size.y, size.z) - delta);

		result->add_uv(Vector2(0.0f, 0.0f));
		result->add_uv(Vector2(1.0f / 3.0f, 0.0f));
		result->add_uv(Vector2(2.0f / 3.0f, 0.0f));
		result->add_uv(Vector2(0.0f, 1.0f / 3.0f));
		result->add_uv(Vector2(1.0f / 3.0f, 1.0f / 3.0f));
		result->add_uv(Vector2(2.0f / 3.0f, 1.0f / 3.0f));
		result->add_uv(Vector2(1.0f, 1.0f / 3.0f));
		result->add_uv(Vector2(0.0f, 2.0f / 3.0f));
		result->add_uv(Vector2(1.0f / 3.0f, 2.0f / 3.0f));
		result->add_uv(Vector2(2.0f / 3.0f, 2.0f / 3.0f));
		result->add_uv(Vector2(1.0f, 2.0f / 3.0f));
		result->add_uv(Vector2(1.0f / 3.0f, 1.0f));
		result->add_uv(Vector2(2.0f / 3.0f, 1.0f));

		// FACE DOWN
		result->add_face(Face({ 1, 2, 3 }, { 4, 1, 3 }, { -1, -1, -1 }));
		result->add_face(Face({ 3, 0, 1 }, { 0, 3, 1 }, { -1, -1, -1 }));

		// FACE TOP
		result->add_face(Face({ 7, 6, 5 }, { 9, 8, 5 }, { -1, -1, -1 }));
		result->add_face(Face({ 5, 4, 7 }, { 4, 5, 8 }, { -1, -1, -1 }));

		// FACE FRONT
		result->add_face(Face({ 4, 5, 1 }, { 5, 4, 2 }, { -1, -1, -1 }));
		result->add_face(Face({ 1, 0, 4 }, { 1, 2, 4 }, { -1, -1, -1 }));

		// FACE BACK
		result->add_face(Face({ 2, 6, 7 }, { 9, 12, 8 }, { -1, -1, -1 }));
		result->add_face(Face({ 7, 3, 2 }, { 11, 8, 12 }, { -1, -1, -1 }));

		// FACE RIGHT
		result->add_face(Face({ 5, 6, 2 }, { 9, 5, 10 }, { -1, -1, -1 }));
		result->add_face(Face({ 2, 1, 5 }, { 6, 10, 5 }, { -1, -1, -1 }));

		// FACE LEFT
		result->add_face(Face({ 3, 7, 4 }, { 8, 7, 4 }, { -1, -1, -1 }));
		result->add_face(Face({ 4, 0, 3 }, { 3, 4, 7 }, { -1, -1, -1 }));

		jgl::Material* tmp_material = new Material("New material");
		tmp_material->ka = color;
		result->set_material(tmp_material);

		if (should_bake == true)
			result->bake();

		return (result);
	}

	Mesh* primitive_plane(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake)
	{
		Mesh* result;
		Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

		result = new Mesh(pos);
		result->rotate(rot);

		result->add_point(Vector3(0.0f, 0.0f, 0.0f) - delta);
		result->add_point(Vector3(size.x, 0.0f, 0.0f) - delta);
		result->add_point(Vector3(size.x, 0.0f, size.z) - delta);
		result->add_point(Vector3(0.0f, 0.0f, size.z) - delta);

		result->add_uv(Vector2(0.0f, 0.0f));
		result->add_uv(Vector2(1.0f, 0.0f));
		result->add_uv(Vector2(0.0f, 1.0f));
		result->add_uv(Vector2(1.0f, 1.0f));

		// FACE DOWN
		result->add_face(Face({ 1, 2, 3 }, { 3, 1, 2 }, { -1, -1, -1 }));
		result->add_face(Face({ 3, 0, 1 }, { 0, 2, 1 }, { -1, -1, -1 }));

		// FACE TOP
		result->add_face(Face({ 3, 2, 1 }, { 3, 2, 1 }, { -1, -1, -1 }));
		result->add_face(Face({ 1, 0, 3 }, { 0, 1, 2 }, { -1, -1, -1 }));

		jgl::Material* tmp_material = new Material("New material");
		tmp_material->ka = color;
		result->set_material(tmp_material);

		if (should_bake == true)
			result->bake();

		return (result);
	}
}