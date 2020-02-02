#include "jgl.h"

c_mesh::c_mesh(Vector3 p_pos, Vector3 p_rot)
{
	_pos = p_pos;

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

c_mesh::c_mesh(string p_path, Vector3 p_pos, Vector3 p_rot) : c_mesh(p_pos, p_rot)
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
				add_face(Face(index_vertices, index_uvs, index_normales, Color(210, 210, 210)));
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

void c_mesh::add_point(Vector3 p_point)
{
	_vertices.push_back(p_point);
}

void c_mesh::add_uv(Vector2 p_uv)
{
	_uvs.push_back(p_uv);
}

void c_mesh::add_normale(Vector3 p_normale)
{
	_normales.push_back(p_normale);
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
	Vector3 b;
	Vector3 c;
	Vector3 tmp;

	_normales.clear();
	for (size_t i = 0; i < _faces.size(); i++)
	{
		b = _rot_matrix * (_vertices[_faces[i].index_vertices[1]] - _vertices[_faces[i].index_vertices[0]]);
		c = _rot_matrix * (_vertices[_faces[i].index_vertices[2]] - _vertices[_faces[i].index_vertices[0]]);
		tmp = b.cross(c).normalize();
		for (size_t j = 0; j < 3; j++)
		{
			if (_faces[i].index_normale[j] == -1)
				_normales.insert(_normales.end(), tmp);
			else
			{
				if (_normales.size() <= _faces[i].index_normale[j] + 1)
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

	_rot_matrix = Matrix(R, _rotation);
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

	rotation = Matrix( R, delta.x, delta.y, delta.z);

	tmp = _pos - target;
	tmp = rotation * tmp;
	_pos = tmp + target;
}

void c_mesh::rotate(Vector3 delta)
{
	_rotation += delta;
	compute_axis();
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



void c_mesh::render_color(c_camera *camera)
{
	if (_baked_vertices.size() == 0)
		return ;

	glUseProgram(g_application->program_color_model());

	glUniform3f(g_application->pos_colorID(), _pos.x, _pos.y, _pos.z);

	glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
	glUniform3f(g_application->pos_colorID(), _pos.x, _pos.y, _pos.z);
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
	glDrawArrays(GL_TRIANGLES, 0, _baked_vertices.size() * 3); // 3 indices starting at 0 -> 1 triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void c_mesh::render_texture(c_camera *camera)
{
	if (_baked_vertices.size() == 0)
		return ;

	glUseProgram(g_application->program_texture_model());

	glBindTexture(GL_TEXTURE_2D, _texture->texture_id());

	glUniformMatrix4fv(g_application->matrix_textureID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
	glUniform3f(g_application->pos_textureID(), _pos.x, _pos.y, _pos.z);
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
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, _baked_vertices.size() * 3); // 3 indices starting at 0 -> 1 triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void c_mesh::render(c_camera *camera)
{
	if (_texture == nullptr)
		render_color(camera);
	else
		render_texture(camera);
}
