#include "jgl.h"

namespace jgl
{
	Mesh_part::Mesh_part(jgl::String p_name)
	{
		_name = p_name;

		glGenBuffers(1, &_vertex_buffer);
		glGenBuffers(1, &_color_buffer);
		glGenBuffers(1, &_normale_buffer);
		glGenBuffers(1, &_uv_buffer);
		glGenBuffers(1, &_alpha_buffer);

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

	void Mesh_part::compute_normales(jgl::Matrix4x4 rot_matrix)
	{
		Vector3 b;
		Vector3 c;
		Vector3 tmp;

		for (size_t i = 0; i < _faces.size(); i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (_faces[i].index_normale[j] == -1)
				{
					b = rot_matrix * (_vertices[_faces[i].index_vertices[0]] - _vertices[_faces[i].index_vertices[1]]);
					c = rot_matrix * (_vertices[_faces[i].index_vertices[2]] - _vertices[_faces[i].index_vertices[0]]);
					tmp = b.cross(c).normalize();
					_normales.insert(_normales.end(), tmp);
					_faces[i].normale = tmp;
				}
				else
				{
					if (_normales.size() <= static_cast<size_t>(_faces[i].index_normale[j] + 1))
						_normales.resize(_faces[i].index_normale[j] + 1);
					_faces[i].normale = _normales[_faces[i].index_normale[j]];
				}
			}
		}
	}

	void Mesh_part::bake(jgl::Matrix4x4 rot_matrix)
	{
		compute_normales(rot_matrix);

		_baked_vertices.clear();
		_baked_uvs.clear();
		_baked_colors.clear();
		_baked_normales.clear();

		_baked_vertices.resize(_faces.size() * 3);
		_baked_uvs.resize(_faces.size() * 3);
		_baked_normales.resize(_faces.size() * 3);
		_baked_colors.resize(_faces.size() * 3);

		for (size_t i = 0; i < _faces.size(); i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				size_t tmp = i * 3 + j;
				if (_faces[i].index_vertices[j] != -1)
				{
					if (size_t(_faces[i].index_vertices[j]) >= _vertices.size())
						jgl::error_exit(1, "Error while baking a Mesh_part with vertices = " + jgl::itoa(_faces[i].index_normale[j]) + " over " + jgl::itoa(_normales.size()) + " possibility");
					_baked_vertices[tmp] = _vertices[_faces[i].index_vertices[j]];
				}
				else
					_baked_vertices[tmp] = Vector3(-1, -1, -1);

				if (_faces[i].index_uvs[j] != -1)
				{
					if (size_t(_faces[i].index_uvs[j]) >= _uvs.size())
						jgl::error_exit(1, "Error while baking a Mesh_part with uvs = " + jgl::itoa(_faces[i].index_normale[j]) + " over " + jgl::itoa(_normales.size()) + " possibility");
					_baked_uvs[tmp] = _uvs[_faces[i].index_uvs[j]];
				}
				else
					_baked_uvs[tmp] = Vector2(-1, -1);

				if (_faces[i].index_normale[j] != -1)
				{
					if (size_t(_faces[i].index_normale[j]) >= _normales.size())
						jgl::error_exit(1, "Error while baking a Mesh_part with normales = " + jgl::itoa(_faces[i].index_normale[j]) + " over " + jgl::itoa(_normales.size()) + " possibility");
					_baked_normales[tmp] = _normales[_faces[i].index_normale[j]];
				}
				else
					_baked_normales[tmp] = _normales[tmp];

				_baked_colors[tmp] = _faces[i].color;
			}
		}

		if (_baked_vertices.size() == 0)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_vertices.size() * 3 * sizeof(float), static_cast<float*>(&(_baked_vertices[0].x)), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_colors.size() * 4 * sizeof(float), static_cast<float*>(&(_baked_colors[0].r)), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_uvs.size() * 2 * sizeof(float), static_cast<float*>(&(_baked_uvs[0].x)), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_normales.size() * 3 * sizeof(float), static_cast<float*>(&(_baked_normales[0].x)), GL_STATIC_DRAW);

	}

	void Mesh_part::render_color(Mesh* parent, Camera* camera, Vector3 p_pos)
	{
		if (_baked_vertices.size() == 0)
			return;

		glUseProgram(g_application->program_color_model());

		glUniformMatrix4fv(g_application->matrix_colorID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
		glUniform3f(g_application->pos_colorID(), p_pos.x, p_pos.y, p_pos.z);
		glUniform3f(g_application->size_colorID(), parent->size().x, parent->size().y, parent->size().z);
		glUniformMatrix4fv(g_application->rot_colorID(), 1, GL_FALSE, &(parent->rot_matrix().value[0][0]));
		glUniform4f(g_application->dir_light_colorID(), camera->dir_light().x, camera->dir_light().y, camera->dir_light().z, 0.0f);

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
		//glEnable(GL_CULL_FACE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDisable(GL_CULL_FACE);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Mesh_part::render_texture(Mesh *parent, Camera* camera, Vector3 p_pos)
	{
		if (_baked_vertices.size() == 0)
			return;

		glUseProgram(g_application->program_texture_model());

		glBindTexture(GL_TEXTURE_2D, _texture->texture_id());

		glUniformMatrix4fv(g_application->matrix_textureID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
		glUniform3f(g_application->pos_textureID(), p_pos.x, p_pos.y, p_pos.z);
		glUniform3f(g_application->size_textureID(), parent->size().x, parent->size().y, parent->size().z);
		glUniformMatrix4fv(g_application->rot_textureID(), 1, GL_FALSE, &(parent->rot_matrix().value[0][0]));
		glUniform4f(g_application->dir_light_textureID(), camera->dir_light().x, camera->dir_light().y, camera->dir_light().z, 0.0f);
		glUniform1f(g_application->alpha_textureID(), parent->transparency());

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
		// glFrontFace(GL_CW);
		// glEnable(GL_CULL_FACE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// glDisable(GL_CULL_FACE);
		// glFrontFace(GL_CW);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Mesh_part::render(Mesh* parent, Camera* camera, Vector3 p_pos)
	{
		if (_texture == nullptr)
			render_color(parent, camera, p_pos);
		else
			render_texture(parent, camera, p_pos);
	}
	
	void Mesh_part::clear()
	{
		_faces.clear();

		_vertices.clear();
		_uvs.clear();
		_normales.clear();

		_baked_vertices.clear();
		_baked_uvs.clear();
		_baked_colors.clear();
		_baked_normales.clear();
	}
	void Mesh_part::clear_baked()
	{
		_faces.clear();
		_baked_vertices.clear();
		_baked_uvs.clear();
		_baked_colors.clear();
		_baked_normales.clear();
	}
}