#include "jgl.h"

c_mesh *primitive_cube(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

	result = new c_mesh(pos);
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
	result->add_face(Face(new int [3]{2, 3, 1}, new int [3]{4, 3, 1}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{0, 1, 3}, new int [3]{0, 1, 3}, new int [3]{-1, -1, -1}, color));

	// FACE TOP
	result->add_face(Face(new int [3]{6, 5, 7}, new int [3]{9, 5, 8}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{4, 7, 5}, new int [3]{4, 8, 5}, new int [3]{-1, -1, -1}, color));

	// FACE FRONT
	result->add_face(Face(new int [3]{5, 1, 4}, new int [3]{5, 2, 4}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{0, 4, 1}, new int [3]{1, 4, 2}, new int [3]{-1, -1, -1}, color));

	// FACE BACK
	result->add_face(Face(new int [3]{6, 7, 2}, new int [3]{9, 8, 12}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{3, 2, 7}, new int [3]{11, 12, 8}, new int [3]{-1, -1, -1}, color));

	// FACE RIGHT
	result->add_face(Face(new int [3]{6, 2, 5}, new int [3]{9, 10, 5}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{1, 5, 2}, new int [3]{6, 5, 10}, new int [3]{-1, -1, -1}, color));

	// FACE LEFT
	result->add_face(Face(new int [3]{7, 4, 3}, new int [3]{8, 4, 7}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{0, 3, 4}, new int [3]{3, 7, 4}, new int [3]{-1, -1, -1}, color));

	if (should_bake == true)
		result->bake();

	return (result);
}

c_mesh *primitive_voxel(Vector3 pos, c_tileset *tileset,
		Vector2 top_sprite, Vector2 side_sprite, Vector2 down_sprite,
		float p_transparency,
		bool should_bake, Vector3 rot, Vector3 size)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

	result = new c_mesh(pos);
	result->set_transparency(p_transparency);
	result->rotate(rot);

	result->add_point(Vector3(0.0f, 0.0f, 0.0f) - delta); // 0
	result->add_point(Vector3(size.x, 0.0f, 0.0f) - delta); // 1
	result->add_point(Vector3(size.x, 0.0f, size.z) - delta); // 2
	result->add_point(Vector3(0.0f, 0.0f, size.z) - delta); // 3
	result->add_point(Vector3(0.0f, size.y, 0.0f) - delta); // 4
	result->add_point(Vector3(size.x, size.y, 0.0f) - delta); // 5
	result->add_point(Vector3(size.x, size.y, size.z) - delta); // 6
	result->add_point(Vector3(0.0f, size.y, size.z) - delta); // 7

		Vector2 tmp_size = tileset->unit();

		// Top face UV
	Vector2 tmp_pos = tileset->sprite(down_sprite);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 8
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 9
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 10
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 11

		// Side face UV
	tmp_pos = tileset->sprite(side_sprite);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 4
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 5
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 6
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 7

		// Down face UV
	tmp_pos = tileset->sprite(top_sprite);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 0
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 1
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 2
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 3

	// FACE DOWN
	result->add_face(Face(new int [3]{2, 3, 1}, new int [3]{2, 3, 1}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 1, 3}, new int [3]{0, 1, 3}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE TOP
	result->add_face(Face(new int [3]{6, 5, 7}, new int [3]{10, 9, 11}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{4, 7, 5}, new int [3]{8, 11, 9}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE FRONT
	result->add_face(Face(new int [3]{5, 1, 4}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 4, 1}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE BACK
	result->add_face(Face(new int [3]{6, 7, 2}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{3, 2, 7}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE RIGHT
	result->add_face(Face(new int [3]{6, 2, 5}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{1, 5, 2}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE LEFT
	result->add_face(Face(new int [3]{7, 4, 3}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 3, 4}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	if (should_bake == true)
		result->bake();

	return (result);
}

c_mesh *primitive_voxel(Vector3 pos, c_tileset *tileset, size_t type, float p_transparency, bool should_bake, Vector3 rot, Vector3 size)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

	result = new c_mesh(pos);
	result->set_transparency(p_transparency);
	result->rotate(rot);

	result->add_point(Vector3(0.0f, 0.0f, 0.0f) - delta); // 0
	result->add_point(Vector3(size.x, 0.0f, 0.0f) - delta); // 1
	result->add_point(Vector3(size.x, 0.0f, size.z) - delta); // 2
	result->add_point(Vector3(0.0f, 0.0f, size.z) - delta); // 3
	result->add_point(Vector3(0.0f, size.y, 0.0f) - delta); // 4
	result->add_point(Vector3(size.x, size.y, 0.0f) - delta); // 5
	result->add_point(Vector3(size.x, size.y, size.z) - delta); // 6
	result->add_point(Vector3(0.0f, size.y, size.z) - delta); // 7

		Vector2 tmp_size = tileset->unit();

		// Top face UV
	Vector2 tmp_pos = tileset->sprite(type * 3);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 8
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 9
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 10
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 11

		// Side face UV
	tmp_pos = tileset->sprite(type * 3 + 1);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 4
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 5
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 6
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 7

		// Down face UV
	tmp_pos = tileset->sprite(type * 3 + 2);
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 0)); // 0
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 0)); // 1
	result->add_uv(tmp_pos + tmp_size * Vector2(1, 1)); // 2
	result->add_uv(tmp_pos + tmp_size * Vector2(0, 1)); // 3

	// FACE DOWN
	result->add_face(Face(new int [3]{2, 3, 1}, new int [3]{2, 3, 1}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 1, 3}, new int [3]{0, 1, 3}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE TOP
	result->add_face(Face(new int [3]{6, 5, 7}, new int [3]{10, 9, 11}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{4, 7, 5}, new int [3]{8, 11, 9}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE FRONT
	result->add_face(Face(new int [3]{5, 1, 4}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 4, 1}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE BACK
	result->add_face(Face(new int [3]{6, 7, 2}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{3, 2, 7}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE RIGHT
	result->add_face(Face(new int [3]{6, 2, 5}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{1, 5, 2}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	// FACE LEFT
	result->add_face(Face(new int [3]{7, 4, 3}, new int [3]{7, 5, 6}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));
	result->add_face(Face(new int [3]{0, 3, 4}, new int [3]{4, 6, 5}, new int [3]{-1, -1, -1}, Color(150, 150, 150)));

	if (should_bake == true)
		result->bake();

	return (result);
}

c_mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector2 size, Color color, bool should_bake)
{
	return (primitive_plane(pos, rot, Vector3(size.x, 0.0f, size.y), color));
}

c_mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake)
{
	c_mesh *result;
	Vector3 delta = Vector3(size.x / 2.0f, 0.0f, size.z / 2.0f);

	result = new c_mesh(pos);
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
	result->add_face(Face(new int [3]{2, 3, 1}, new int [3]{3, 2, 1}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{0, 1, 3}, new int [3]{0, 1, 2}, new int [3]{-1, -1, -1}, color));

	// FACE TOP
	result->add_face(Face(new int [3]{2, 1, 3}, new int [3]{3, 1, 2}, new int [3]{-1, -1, -1}, color));
	result->add_face(Face(new int [3]{0, 3, 1}, new int [3]{0, 2, 1}, new int [3]{-1, -1, -1}, color));

	if (should_bake == true)
		result->bake();

	return (result);
}
