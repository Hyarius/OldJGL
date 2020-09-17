#include "jgl.h"

namespace jgl
{
	Image* Material::_empty_texture = nullptr;

	Material* Mesh::_base_material = nullptr;
	Material* Mesh_part::_base_material = nullptr;

	Mesh_part::Mesh_part(const jgl::String p_name)
	{

		_name = p_name.copy();

		glGenBuffers(1, &_vertex_buffer);
		glGenBuffers(1, &_normale_buffer);
		glGenBuffers(1, &_uv_buffer);

		_faces.clear();

		_vertices->clear();
		_uvs->clear();
		_normales->clear();

		_material = _base_material;
	}

	void Mesh_part::compute_normales(const jgl::Matrix4x4 rot_matrix)
	{
		Vector3 b;
		Vector3 c;
		Vector3 tmp;

		for (size_t i = 0; i < _faces.size(); i++)
		{
			if (_faces[i].index_normale[0] == -1)
			{
				if (_faces[i].index_vertices[0] < 0 || _faces[i].index_vertices[1] < 0 || _faces[i].index_vertices[2] < 0)
				{
					tmp = -1;
				}
				else
				{
					b = (_vertices->operator[](_faces[i].index_vertices[0]) - _vertices->operator[](_faces[i].index_vertices[1]));
					c = (_vertices->operator[](_faces[i].index_vertices[0]) - _vertices->operator[](_faces[i].index_vertices[2]));
					tmp = rot_matrix * b.cross(c).normalize();
				}
				
				_normales->insert(_normales->end(), tmp);
				_normales->insert(_normales->end(), tmp);
				_normales->insert(_normales->end(), tmp);
			}
		}
	}

	void Mesh_part::bake(const jgl::Matrix4x4 rot_matrix)
	{
		compute_normales(rot_matrix);

		_baked_vertices.clear();
		_baked_uvs.clear();
		_baked_normales.clear();

		_baked_vertices.resize(_faces.size() * 3);
		_baked_uvs.resize(_faces.size() * 3);
		_baked_normales.resize(_faces.size() * 3);

		for (size_t i = 0; i < _faces.size(); i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				size_t tmp = i * 3 + j;
				if (_faces[i].index_vertices[j] != -1)
				{
					if (size_t(_faces[i].index_vertices[j]) >= _vertices->size())
						jgl::error_exit(1, "Error while baking a Mesh_part with vertices = " + jgl::itoa(_faces[i].index_vertices[j]) + " over " + jgl::itoa(_vertices->size()) + " possibility");
					_baked_vertices[tmp] = _vertices->operator[](_faces[i].index_vertices[j]);
				}
				else
					_baked_vertices[tmp] = Vector3(-1, -1, -1);

				if (_faces[i].index_uvs[j] != -1)
				{
					if (size_t(_faces[i].index_uvs[j]) >= _uvs->size())
						jgl::error_exit(1, "Error while baking a Mesh_part with uvs = " + jgl::itoa(_faces[i].index_uvs[j]) + " over " + jgl::itoa(_uvs->size()) + " possibility");
					_baked_uvs[tmp] = _uvs->operator[](_faces[i].index_uvs[j]);
				}
				else
					_baked_uvs[tmp] = Vector2(-1, -1);

				if (_faces[i].index_normale[j] != -1)
				{
					if (size_t(_faces[i].index_normale[j]) >= _normales->size())
						jgl::error_exit(1, "Error while baking a Mesh_part with normales = " + jgl::itoa(_faces[i].index_normale[j]) + " over " + jgl::itoa(_normales->size()) + " possibility");
					_baked_normales[tmp] = _normales->operator[](_faces[i].index_normale[j]);
				}
				else
					_baked_normales[tmp] = _normales->operator[](tmp);
			}
		}

		const Vector3* tmp = _baked_vertices.all();
		const Vector2* tmp2 = _baked_uvs.all();
		const Vector3* tmp3 = _baked_normales.all();

		if (_baked_vertices.size() == 0)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_vertices.size() * 3 * sizeof(float), static_cast<const float*>(&(tmp[0].x)), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_uvs.size() * 2 * sizeof(float), static_cast<const float*>(&(tmp2[0].x)), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
		glBufferData(GL_ARRAY_BUFFER, _baked_normales.size() * 3 * sizeof(float), static_cast<const float*>(&(tmp3[0].x)), GL_STATIC_DRAW);
	}

	void Mesh_part::render_color(const Mesh* parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport)
	{
		if (_baked_vertices.size() == 0)
			return;

		if (viewport != nullptr)
			viewport->use();

		glUseProgram(g_application->program_color_model());

		glUniform3f(g_application->pos_colorID(), p_pos.x, p_pos.y, p_pos.z);
		glUniformMatrix4fv(g_application->rot_colorID(), 1, GL_FALSE, &(parent->rot_matrix().value[0][0]));
		glUniform3f(g_application->size_colorID(), parent->size().x, parent->size().y, parent->size().z);
		glUniformMatrix4fv(g_application->MVP_colorID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
		glUniformMatrix4fv(g_application->view_matrix_colorID(), 1, GL_FALSE, &(camera->view().value[0][0]));
		glUniformMatrix4fv(g_application->model_matrix_colorID(), 1, GL_FALSE, &(camera->model().value[0][0]));

		glUniform3f(g_application->light_pos_colorID(), camera->light_pos().x, camera->light_pos().y, camera->light_pos().z);
		glUniform4f(g_application->light_dir_colorID(), camera->light_dir().x, camera->light_dir().y, camera->light_dir().z, 0.0f);
		glUniform3f(g_application->camera_dir_colorID(), camera->direction().x, camera->direction().y, camera->direction().z);

		glUniform4f(g_application->material_ka_colorID(), _material->ka.r, _material->ka.g, _material->ka.b, _material->ka.a);
		glUniform4f(g_application->material_kd_colorID(), _material->kd.r, _material->kd.g, _material->kd.b, _material->kd.a);
		glUniform4f(g_application->material_ks_colorID(), _material->ks.r, _material->ks.g, _material->ks.b, _material->ks.a);
		glUniform4f(g_application->material_ke_colorID(), _material->ke.r, _material->ke.g, _material->ke.b, _material->ke.a);

		glUniform1f(g_application->material_ns_colorID(), _material->ns);
		glUniform1f(g_application->material_ni_colorID(), _material->ni);
		glUniform1f(g_application->material_d_colorID(), _material->d);

		glUniform1f(g_application->alpha_colorID(), parent->transparency());

		glUniform1i(g_application->material_illum_colorID(), _material->illum);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2rst attribute buffer : vertices

		// 3rst attribute buffer : vertices
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _normale_buffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		//glEnable(GL_CULL_FACE);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glDisable(GL_CULL_FACE);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void Mesh_part::render_texture(const Mesh* parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport)
	{
		if (_baked_vertices.size() == 0)
			return;

		if (viewport != nullptr)
			viewport->use();

		glUseProgram(g_application->program_texture_model());

		glUniform3f(g_application->pos_textureID(), p_pos.x, p_pos.y, p_pos.z);
		glUniformMatrix4fv(g_application->rot_textureID(), 1, GL_FALSE, &(parent->rot_matrix().value[0][0]));
		glUniform3f(g_application->size_textureID(), parent->size().x, parent->size().y, parent->size().z);
		glUniformMatrix4fv(g_application->MVP_textureID(), 1, GL_FALSE, &(camera->MVP().value[0][0]));
		glUniformMatrix4fv(g_application->view_matrix_textureID(), 1, GL_FALSE, &(camera->view().value[0][0]));
		glUniformMatrix4fv(g_application->model_matrix_textureID(), 1, GL_FALSE, &(camera->model().value[0][0]));

		glUniform3f(g_application->light_pos_textureID(), camera->light_pos().x, camera->light_pos().y, camera->light_pos().z);
		glUniform4f(g_application->light_dir_textureID(), camera->light_dir().x, camera->light_dir().y, camera->light_dir().z, 0.0f);
		glUniform3f(g_application->camera_dir_textureID(), camera->direction().x, camera->direction().y, camera->direction().z);

		glUniform4f(g_application->material_ka_textureID(), _material->ka.r, _material->ka.g, _material->ka.b, _material->ka.a);
		glUniform4f(g_application->material_kd_textureID(), _material->kd.r, _material->kd.g, _material->kd.b, _material->kd.a);
		glUniform4f(g_application->material_ks_textureID(), _material->ks.r, _material->ks.g, _material->ks.b, _material->ks.a);
		glUniform4f(g_application->material_ke_textureID(), _material->ke.r, _material->ke.g, _material->ke.b, _material->ke.a);

		glUniform1f(g_application->material_ns_textureID(), _material->ns);
		glUniform1f(g_application->material_ni_textureID(), _material->ni);
		glUniform1f(g_application->material_d_textureID(), _material->d);

		glUniform1f(g_application->alpha_textureID(), parent->transparency());

		glUniform1i(g_application->material_illum_textureID(), _material->illum);

		glBindTexture(GL_TEXTURE_2D, _material->diffuse_texture->texture_id());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _material->diffuse_texture->texture_id());
		glUniform1i(g_application->material_diffuse_texture_textureID(), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _material->normal_texture->texture_id());
		glUniform1i(g_application->material_normal_texture_textureID(), 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _material->specular_texture->texture_id());
		glUniform1i(g_application->material_specular_texture_textureID(), 2);

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
		// glDepthFunc(GL_ALWAYS);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_baked_vertices.size() * 3)); // 3 indices starting at 0 -> 1 triangle
		// glDepthFunc(GL_LEQUAL);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// glDisable(GL_CULL_FACE);
		// glFrontFace(GL_CW);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Mesh_part::render(const Mesh* parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport)
	{
		if (_material->diffuse_texture == Material::empty_texture() || _uvs->size() == 0)
			render_color(parent, camera, p_pos, viewport);
		else
			render_texture(parent, camera, p_pos, viewport);
	}
	
	void Mesh_part::clear()
	{
		_vertices->clear();
		_uvs->clear();
		_normales->clear();

		clear_baked();
	}
	void Mesh_part::clear_baked()
	{
		_faces.clear();

		_baked_vertices.clear();
		_baked_uvs.clear();
		_baked_normales.clear();
	}
}