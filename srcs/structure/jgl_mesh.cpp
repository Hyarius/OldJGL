#include "jgl.h"

c_mesh::c_mesh(Vector3 p_pos, Vector3 p_rot, Vector3 p_size)
{
	_pos = p_pos;
	_size = p_size;
	_velocity = 0;
	_kinetic = false;

	glGenBuffers(1, &_vertex_buffer);
	glGenBuffers(1, &_color_buffer);
	glGenBuffers(1, &_normale_buffer);
	glGenBuffers(1, &_uv_buffer);
	glGenBuffers(1, &_alpha_buffer);

	_rotation = p_rot;
	compute_axis();

	_transparency = 1.0f;
	_faces.clear();

	_vertices.clear();
	_uvs.clear();
	_normales.clear();

	_baked_vertices.clear();
	_baked_uvs.clear();
	_baked_colors.clear();
	_baked_normales.clear();

	_texture = nullptr;
}

c_mesh::c_mesh(string p_path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color) : c_mesh(p_pos, p_rot)
{
	int index_vertices[3] = {-1, -1, -1}, index_uvs[3] = {-1, -1, -1}, index_normales[3] = {-1, -1, -1};
	vector<string> tab;
	vector<string> face_content;
	fstream file = open_file(p_path, ios_base::in | ios_base::out);

	while (file.eof() == false)
	{
		tab = get_strsplit(file, " ");
		if (tab.size() != 0)
		{
			if (tab[0] == "v")
				add_point(Vector3(atof(tab[1].c_str()), atof(tab[2].c_str()), atof(tab[3].c_str())));
			else if (tab[0] == "vt")
				add_uv(Vector2(atof(tab[1].c_str()), atof(tab[2].c_str())));
			else if (tab[0] == "vn")
				add_normale(Vector3(atof(tab[1].c_str()), atof(tab[2].c_str()), atof(tab[3].c_str())));
			else if (tab[0] == "f")
			{
				for (size_t i = 0; i < 3; i++)
				{
					face_content = strsplit(tab[i + 1], "/", false);
					index_vertices[i] = atoi(face_content[0].c_str()) - 1;
					if (face_content.size() >= 2)
						index_uvs[i] = (face_content[1].length() == 0 ? -1 : atoi(face_content[1].c_str()) - 1);
					if (face_content.size() >= 3)
						index_normales[i] = (face_content[2].length() == 0 ? -1 : atoi(face_content[2].c_str()) - 1);
				}
				add_face(Face(index_vertices, index_uvs, index_normales, color));
				for (size_t i = 0; i < 3; i++)
				{
					index_vertices[i] = -1;
					index_uvs[i] = -1;
					index_normales[i] = -1;
				}
			}
		}
	}
	bake();
}

void c_mesh::compute_normales()
{
	Vector3 b;
	Vector3 c;
	Vector3 tmp;

	_normales.clear();
	for (size_t i = 0; i < _faces.size(); i++)
	{
		b = _rot_matrix * (_vertices[_faces[i].index_vertices[1]] - _vertices[_faces[i].index_vertices[0]]);
		c = _rot_matrix * (_vertices[_faces[i].index_vertices[2]] - _vertices[_faces[i].index_vertices[0]]);
		tmp = b.cross(c).normalize();
		_faces[i].normale = tmp;
		for (size_t j = 0; j < 3; j++)
		{
			if (_faces[i].index_normale[j] == -1)
				_normales.insert(_normales.end(), tmp);
			else
			{
				if (_normales.size() <= static_cast<size_t>(_faces[i].index_normale[j] + 1))
					_normales.resize(_faces[i].index_normale[j] + 1);
				_normales[_faces[i].index_normale[j]] = tmp;
			}
		}
	}
}

void c_mesh::compute_axis()
{
	float tmp_yaw = degree_to_radius(_rotation.y);
	float tmp_pitch = degree_to_radius(_rotation.z);

	_rot_matrix = Matrix(Matrix_type::rotation, _rotation);
	_rot_matrix.value[3][3] = 1.0f;
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
	compute_axis();
}

void c_mesh::rotate_around_point(Vector3 target, Vector3 delta)
{
	Vector3 tmp;
	Matrix rotation;

	rotation = Matrix(Matrix_type::rotation, delta.x, delta.y, delta.z);

	tmp = _pos - target;
	tmp = rotation * tmp;
	_pos = tmp + target;
}

void c_mesh::rotate(Vector3 delta)
{
	_rotation += delta;
	compute_axis();
}

void c_mesh::compute_bubble_box()
{
	Vector3 total;

	total = 0;
	for (size_t i = 0; i < _vertices.size(); i++)
		total += _vertices[i];
	_center = total / static_cast<int>(_vertices.size());
	_radius = 0;
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		float tmp_radius = _center.distance(_vertices[i]);
		if (_radius < tmp_radius)
			_radius = tmp_radius;
	}
}

void c_mesh::bake()
{
	compute_bubble_box();
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

			if (_faces[i].index_normale[j] != -1)
				_baked_normales.push_back(_normales[_faces[i].index_normale[j]]);
			else
				_baked_normales.push_back(_normales[i * 3 + j]);

			_baked_colors.push_back(_faces[i].color);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_vertices.size() * 3 * sizeof(float), static_cast<float *>(&(_baked_vertices[0].x)), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_colors.size() * 4 * sizeof(float), static_cast<float *>(&(_baked_colors[0].r)), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_uvs.size() * 2 * sizeof(float), static_cast<float *>(&(_baked_uvs[0].x)), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
	glBufferData(GL_ARRAY_BUFFER, _baked_normales.size() * 3 * sizeof(float), static_cast<float *>(&(_baked_normales[0].x)), GL_STATIC_DRAW);

}

void c_mesh::render_color_differed(c_camera *camera, Vector3 p_pos)
{
	if (_baked_vertices.size() == 0)
		return ;

	glUseProgram(g_application->program_color_model());

	glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
	glUniform3f(g_application->pos_colorID(), p_pos.x, p_pos.y, p_pos.z);
	glUniformMatrix4fv(g_application->rot_colorID(), 1, GL_FALSE, &(_rot_matrix.value[0][0]));
	glUniform3f(g_application->dir_light_textureID(), camera->dir_light().x, camera->dir_light().y, camera->dir_light().z);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2rst attribute buffer : vertices
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 3rst attribute buffer : vertices
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void c_mesh::render_texture_differed(c_camera *camera, Vector3 p_pos)
{
	if (_baked_vertices.size() == 0)
		return ;

	glUseProgram(g_application->program_texture_model());

	glBindTexture(GL_TEXTURE_2D, _texture->texture_id());

	glUniformMatrix4fv(g_application->matrix_textureID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
	glUniform3f(g_application->pos_textureID(), p_pos.x, p_pos.y, p_pos.z);
	glUniformMatrix4fv(g_application->rot_textureID(), 1, GL_FALSE, &(_rot_matrix.value[0][0]));
	glUniform3f(g_application->dir_light_textureID(), camera->dir_light().x, camera->dir_light().y, camera->dir_light().z);
	glUniform1f(g_application->alpha_textureID(), _transparency);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2rst attribute buffer : uv
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 3rst attribute buffer : normales
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	// glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void c_mesh::render_differed(c_camera *camera, Vector3 p_pos)
{
	if (_texture == nullptr)
		render_color_differed(camera, p_pos);
	else
		render_texture_differed(camera, p_pos);
}

void c_mesh::add_component(c_mesh *mesh, Vector3 p_pos)
{
	size_t index_actual_vertices;
	size_t index_actual_uvs;
	size_t index_actual_normales;

	index_actual_vertices = _vertices.size();
	index_actual_uvs = _uvs.size();
	index_actual_normales = _normales.size();
	for (size_t i = 0; i < mesh->vertices().size(); i++)
		add_point(mesh->vertices()[i] + p_pos);
	for (size_t i = 0; i < mesh->uvs().size(); i++)
		add_uv(mesh->uvs()[i]);
	for (size_t i = 0; i < mesh->normales().size(); i++)
		add_normale(mesh->normales()[i]);

	for (size_t i = 0; i < mesh->faces().size(); i++)
	{
		Face *actual;

		actual = mesh->faces(i);
		add_face(Face(new int [3]{
			actual->index_vertices[0] + static_cast<int>(index_actual_vertices),
			actual->index_vertices[1] + static_cast<int>(index_actual_vertices),
			actual->index_vertices[2] + static_cast<int>(index_actual_vertices)
		}, new int[3]{
			(actual->index_uvs[0] == -1 ? -1 : actual->index_uvs[0] + static_cast<int>(index_actual_uvs)),
			(actual->index_uvs[1] == -1 ? -1 : actual->index_uvs[1] + static_cast<int>(index_actual_uvs)),
			(actual->index_uvs[2] == -1 ? -1 : actual->index_uvs[2] + static_cast<int>(index_actual_uvs))
		}, new int[3]{
			(actual->index_normale[0] == -1 ? -1 : actual->index_normale[0] + static_cast<int>(index_actual_normales)),
			(actual->index_normale[1] == -1 ? -1 : actual->index_normale[1] + static_cast<int>(index_actual_normales)),
			(actual->index_normale[2] == -1 ? -1 : actual->index_normale[2] + static_cast<int>(index_actual_normales))
		}));
	}
}
