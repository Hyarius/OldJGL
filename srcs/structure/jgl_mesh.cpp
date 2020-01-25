#include "jgl.h"

c_mesh::c_mesh(Vector3 p_pos)
{
	_pos = p_pos;

	glGenBuffers(1, &_vertex_buffer);
	glGenBuffers(1, &_color_buffer);
	glGenBuffers(1, &_uv_buffer);
	glGenBuffers(1, &_alpha_buffer);

	_rotation = Vector3(0, 0, 0);
	_forward = Vector3(1, 0, 0);
	_right = Vector3(0, 0, 1);
	_up = Vector3(0, 1, 0);

	_faces.clear();

	_vertices.clear();
	_uvs.clear();

	_baked_vertices.clear();
	_baked_uvs.clear();
	_baked_colors.clear();
	_baked_normales.clear();

	_texture = nullptr;
}

void c_mesh::add_point(Vector3 p_point)
{
	_vertices.push_back(p_point);
}

void c_mesh::add_uv(Vector2 p_uv)
{
	_uvs.push_back(p_uv);
}

void c_mesh::add_face(Face p_face)
{
	_faces.push_back(p_face);
}

void c_mesh::set_texture(c_image *p_texture)
{
	_texture = p_texture;
}

void c_mesh::compute_normales()
{
	Vector3 a;
	Vector3 b;
	Vector3 c;

	for (size_t i = 0; i < _faces.size(); i++)
	{
		a = _vertices[_faces[i].index_vertices[0]];
		b = _vertices[_faces[i].index_vertices[1]] - _vertices[_faces[i].index_vertices[0]];
		c = _vertices[_faces[i].index_vertices[2]] - _vertices[_faces[i].index_vertices[0]];
		_faces[i].normale = (b.cross(c)).normalize();
	}
}

void c_mesh::compute_axis()
{
	float tmp_yaw = degree_to_radius(_rotation.y);
	float tmp_pitch = degree_to_radius(_rotation.z);

	_forward = (Vector3( sin(tmp_yaw - 3.14f / 2.0f), 0.0f, cos(tmp_yaw - 3.14f / 2.0f))).normalize();
	_right = (Vector3(cos(tmp_pitch) * sin(tmp_yaw), sin(tmp_pitch), cos(tmp_pitch) * cos(tmp_yaw)) ).normalize();
	_up = ((_forward).cross(_right)).normalize();
}

void c_mesh::look_at(Vector3 target)
{
	Vector3	result;

	result = (_pos - target).normalize();
	_rotation.y = radius_to_degree(atan2(result.z, -result.x)) - 90;
	_rotation.z = radius_to_degree(atan2(result.y,
				sqrt(result.x * result.x + result.z * result.z)));
	_rotation.z = clamp_float(-89, _rotation.z, 89);
	bake();
}

void c_mesh::rotate_around_point(Vector3 target, Vector3 delta)
{
	Matrix translate;
	Matrix axis_mat;
	Matrix inv_axis_mat;
	Matrix rotation;
	Matrix inv_translate;
	int			i;

	translate = Matrix( T, target - _pos);
	inv_translate = Matrix( T, (target - _pos).invert());
	rotation = Matrix( R, delta.x, delta.y, delta.z);
	_rotation += delta;
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i] = inv_translate * _vertices[i];
		_vertices[i] = rotation * _vertices[i];
		_vertices[i] = translate * _vertices[i];
	}
	bake();
}

void c_mesh::rotate(Vector3 delta)
{
	rotate_around_point(_pos, delta);
}

void c_mesh::move(Vector3 delta)
{
	_pos += delta;
}

void c_mesh::place(Vector3 p_pos)
{
	_pos = p_pos;
}

void c_mesh::bake()
{
	compute_normales();

	_baked_vertices.clear();
	_baked_uvs.clear();
	_baked_colors.clear();
	_baked_normales.clear();

	for (size_t i = 0; i < _faces.size(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (_faces[i].index_vertices[j] != -1)
				_baked_vertices.push_back(_vertices[_faces[i].index_vertices[j]]);
			else
				_baked_vertices.push_back(Vector3(-1, -1, -1));
			if (_faces[i].index_uvs[j] != -1)
				_baked_uvs.push_back(_uvs[_faces[i].index_uvs[j]]);
			else
				_baked_uvs.push_back(Vector2(-1, -1));
			_baked_colors.push_back(_faces[i].color);
			_baked_normales.push_back(_faces[i].normale);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_vertices.size() * 3 * sizeof(float), static_cast<float *>(&(_baked_vertices[0].x)), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_colors.size() * 4 * sizeof(float), static_cast<float *>(&(_baked_colors[0].r)), GL_STATIC_DRAW);
}

void c_mesh::render(Matrix &MVP)
{
	if (_baked_vertices.size() == 0)
		return ;

	glUseProgram(g_application->program_color_model());

	glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, &(MVP.value[0][0]));
	glUniform3f(g_application->pos_colorID(), _pos.x, _pos.y, _pos.z);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, _baked_vertices.size() * 3); // 3 indices starting at 0 -> 1 triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
