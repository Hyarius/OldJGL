#include "jgl.h"

c_mesh *primitive_cube(Vector3 pos, Vector3 size, Color color)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

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

	// set_t_face_vertices(&tmp_face1, 2, 3, 1); // FACE DOWN
	// set_t_face_uvs(&tmp_face1, 4, 3, 1);
	// set_t_face_vertices(&tmp_face2, 0, 1, 3);
	// set_t_face_uvs(&tmp_face2, 0, 1, 3);
	result->add_face(Face((int []){2, 3, 1}, (int []){-1, -1, -1}, Color(255, 0, 0)));
	result->add_face(Face((int []){0, 1, 3}, (int []){-1, -1, -1}, Color(255, 0, 0)));

	// set_t_face_vertices(&tmp_face1, 6, 5, 7); // FACE TOP
	// set_t_face_uvs(&tmp_face1, 9, 5, 8);
	// set_t_face_vertices(&tmp_face2, 4, 7, 5);
	// set_t_face_uvs(&tmp_face2, 4, 8, 5);
	result->add_face(Face((int []){6, 5, 7}, (int []){-1, -1, -1}, Color(0, 255, 0)));
	result->add_face(Face((int []){4, 7, 5}, (int []){-1, -1, -1}, Color(0, 255, 0)));

	// set_t_face_vertices(&tmp_face1, 5, 1, 4); // FACE FRONT
	// set_t_face_uvs(&tmp_face1, 5, 2, 4);
	// set_t_face_vertices(&tmp_face2, 0, 4, 1);
	// set_t_face_uvs(&tmp_face2, 1, 4, 2);
	result->add_face(Face((int []){5, 1, 4}, (int []){-1, -1, -1}, Color(0, 0 ,255)));
	result->add_face(Face((int []){0, 4, 1}, (int []){-1, -1, -1}, Color(0, 0 ,255)));

	// set_t_face_vertices(&tmp_face1, 6, 7, 2); // FACE BACK
	// set_t_face_uvs(&tmp_face1, 9, 8, 12);
	// set_t_face_vertices(&tmp_face2, 3, 2, 7);
	// set_t_face_uvs(&tmp_face2, 11, 12, 8);
	result->add_face(Face((int []){6, 7, 2}, (int []){-1, -1, -1}, Color(255, 0, 255)));
	result->add_face(Face((int []){3, 2, 7}, (int []){-1, -1, -1}, Color(255, 0, 255)));

	// set_t_face_vertices(&tmp_face1, 6, 2, 5); // FACE RIGHT
	// set_t_face_uvs(&tmp_face1, 9, 10, 5);
	// set_t_face_vertices(&tmp_face2, 1, 5, 2);
	// set_t_face_uvs(&tmp_face2, 6, 5, 10);
	result->add_face(Face((int []){6, 2, 5}, (int []){-1, -1, -1}, Color(255, 255, 0)));
	result->add_face(Face((int []){1, 5, 2}, (int []){-1, -1, -1}, Color(255, 255, 0)));

	// set_t_face_vertices(&tmp_face1, 7, 4, 3); // FACE LEFT
	// set_t_face_uvs(&tmp_face1, 8, 4, 7);
	// set_t_face_vertices(&tmp_face2, 0, 3, 4);
	// set_t_face_uvs(&tmp_face2, 3, 7, 4);
	result->add_face(Face((int []){7, 4, 3}, (int []){8, 4, 7}, Color(0, 255, 255)));
	result->add_face(Face((int []){0, 3, 4}, (int []){3, 7, 4}, Color(0, 255, 255)));

	result->bake();

	return (result);
}
