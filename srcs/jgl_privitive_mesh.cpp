#include "jgl.h"

c_mesh *primitive_cube(Vector3 pos, Vector3 size, Color color)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

	result = new c_mesh(pos);

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
	result->add_face(Face((int []){2, 3, 1}, (int []){4, 3, 1}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){0, 1, 3}, (int []){0, 1, 3}, (int []){-1, -1, -1}, color));

	// FACE TOP
	result->add_face(Face((int []){6, 5, 7}, (int []){9, 5, 8}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){4, 7, 5}, (int []){4, 8, 5}, (int []){-1, -1, -1}, color));

	// FACE FRONT
	result->add_face(Face((int []){5, 1, 4}, (int []){5, 2, 4}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){0, 4, 1}, (int []){1, 4, 2}, (int []){-1, -1, -1}, color));

	// FACE BACK
	result->add_face(Face((int []){6, 7, 2}, (int []){9, 8, 12}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){3, 2, 7}, (int []){11, 12, 8}, (int []){-1, -1, -1}, color));

	// FACE RIGHT
	result->add_face(Face((int []){6, 2, 5}, (int []){9, 10, 5}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){1, 5, 2}, (int []){6, 5, 10}, (int []){-1, -1, -1}, color));

	// FACE LEFT
	result->add_face(Face((int []){7, 4, 3}, (int []){8, 4, 7}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){0, 3, 4}, (int []){3, 7, 4}, (int []){-1, -1, -1}, color));

	result->bake();

	return (result);
}

c_mesh *primitive_plane(Vector3 pos, Vector2 size, Color color)
{
	return (primitive_plane(pos, Vector3(size.x, 0.0f, size.y), color));
}

c_mesh *primitive_plane(Vector3 pos, Vector3 size, Color color)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

	result = new c_mesh(pos);

	result->add_point(Vector3(0.0f, 0.0f, 0.0f) - delta);
	result->add_point(Vector3(size.x, 0.0f, 0.0f) - delta);
	result->add_point(Vector3(size.x, 0.0f, size.z) - delta);
	result->add_point(Vector3(0.0f, 0.0f, size.z) - delta);

	result->add_uv(Vector2(0.0f, 0.0f));
	result->add_uv(Vector2(1.0f, 0.0f));
	result->add_uv(Vector2(0.0f, 1.0f));
	result->add_uv(Vector2(1.0f, 1.0f));

	// FACE DOWN
	result->add_face(Face((int []){2, 3, 1}, (int []){3, 2, 1}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){0, 1, 3}, (int []){0, 1, 2}, (int []){-1, -1, -1}, color));

	// FACE TOP
	result->add_face(Face((int []){2, 1, 3}, (int []){3, 1, 2}, (int []){-1, -1, -1}, color));
	result->add_face(Face((int []){0, 3, 1}, (int []){0, 2, 1}, (int []){-1, -1, -1}, color));

	result->bake();

	return (result);
}
