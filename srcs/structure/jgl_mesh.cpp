#include "jgl.h"

namespace jgl
{
	Mesh::Mesh(Vector3 p_pos, Vector3 p_rot, Vector3 p_size)
	{
		_pos = p_pos;
		_size = p_size;
		_velocity = 0;
		_kinetic = false;

		_rotation = p_rot;
		compute_axis();

		_transparency = 1.0f;
	}

	int face_index_value[2][3] = {
		{3, 2, 1},
		{4, 3, 1}
	};

	static void compose_face(jgl::Mesh *target, std::vector<jgl::String> tab, int type, Color color, size_t index)
	{
		std::vector<jgl::String> face_content;
		int index_vertices[3] = { -1, -1, -1 }, index_uvs[3] = { -1, -1, -1 }, index_normales[3] = { -1, -1, -1 };
		int delta_vertice_index = 0;
		int delta_uvs_index = 0;
		int delta_normale_index = 0;

		for (size_t i = 0; i < index; i++)
		{
			Mesh_part* tmp = target->parts(i);
			if (tmp == nullptr)
				error_exit(1, "No part inside mesh");
			delta_vertice_index += tmp->vertices().size();
			delta_uvs_index += tmp->uvs().size();
			delta_normale_index += tmp->normales().size();
		}

		for (size_t i = 0; i < 3; i++)
		{
			strsplit(face_content, tab[face_index_value[type][i]], "/", false);
			index_vertices[i] = stoi(face_content[0]) - 1 - delta_vertice_index;
			if (face_content.size() >= 2)
				index_uvs[i] = (face_content[1].size() == 0 ? -1 : stoi(face_content[1]) - 1 - delta_uvs_index);
			if (face_content.size() >= 3)
				index_normales[i] = (face_content[2].size() == 0 ? -1 : stoi(face_content[2]) - 1 - delta_normale_index);
		}
		target->add_face(Face(index_vertices, index_uvs, index_normales), index);
	}

	static jgl::String create_address(jgl::String path)
	{
		std::vector<jgl::String> tab = strsplit(path, "/");
		jgl::String result = "";

		for (size_t i = 0; i < tab.size() - 1; i++)
			result += tab[i] + "/";

		return (result);
	}

	jgl::Color create_color_from_tab(std::vector<jgl::String> tab)
	{
		return (Color(stof(tab[1]), stof(tab[2]), stof(tab[3])));
	}

	void Mesh::parse_materials(jgl::String p_path)
	{
		Material* material = nullptr;
		std::fstream file = open_file(p_path, std::ios_base::in | std::ios_base::out);
		jgl::String line;
		std::vector<jgl::String> tab;
		jgl::String address = create_address(p_path);

		while (file.eof() == false)
		{
			line = get_str(file);
			if (line.size() != 0 && line[0] != '#')
			{
				strsplit(tab, line, " ");
				if (tab[0] == "newmtl")
				{
					if (material != nullptr)
						_materials.push_back(material);
					material = new Material(tab[1]);
				}
				// Ambient Color
				else if (tab[0] == "Ka")
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ka construction");

					material->ka = create_color_from_tab(tab);
				}
				// Diffuse Color
				else if (tab[0] == "Kd")
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Kd construction");

					material->kd = create_color_from_tab(tab);
				}
				// Specular Color
				else if (tab[0] == "Ks")
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ks construction");

					material->ks = create_color_from_tab(tab);
				}
				// Specular Exponent
				else if (tab[0] == "Ns")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in Ns construction");

					material->ns = stof(tab[1]);
				}
				else if (tab[0] == "Ke")
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ke construction");

					material->ke = create_color_from_tab(tab);
				}
				// Optical Density
				else if (tab[0] == "Ni")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in Ni construction");

					material->ni = stof(tab[1]);
				}
				// Dissolve
				else if (tab[0] == "d")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in D construction");

					material->d = stof(tab[1]);
				}
				// Illumination
				else if (tab[0] == "illum")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in illum construction");

					material->illum = stoi(tab[1]);
				}
				// Ambient Texture Map
				else if (tab[0] == "map_Ka")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ka construction");

					material->ambiant_texture = new Image(tab[1]);
				}
				// Diffuse Texture Map
				else if (tab[0] == "map_Kd")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Kd construction");

					material->diffuse_texture = new Image(address + tab[1]);
				}
				// Specular Texture Map
				else if (tab[0] == "map_Ks")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ks construction");

					material->specular_texture = new Image(address + tab[1]);
				}
				// Specular Hightlight Map
				else if (tab[0] == "map_Ns")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ns construction");

					material->specular_hight_light = new Image(address + tab[1]);
				}
				// Alpha Texture Map
				else if (tab[0] == "map_d")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Kd construction");

					material->alpha_texture = new Image(address + tab[1]);
				}
				// Bump Map
				else if (tab[0] == "map_Bump" || tab[0] == "map_bump" || tab[0] == "bump")
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in bump map construction");

					material->bump = new Image(address + tab[1]);
				}

			}
		}
		if (material != nullptr)
			_materials.push_back(material);
	}

	Material* Mesh::find_material(jgl::String p_name)
	{
		for (size_t i = 0; i < _materials.size(); i++)
		{

			if (_materials[i]->name == p_name)
				return (_materials[i]);
		}
		return (jgl_base_material);
	}

	Mesh::Mesh(jgl::String p_path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color) : Mesh(p_pos, p_rot, p_size)
	{
		int tmp_part_index = -1;
		jgl::String line;
		std::vector<jgl::String> tab;
		std::fstream file = open_file(p_path, std::ios_base::in | std::ios_base::out);
		jgl::String address = create_address(p_path);

		while (file.eof() == false)
		{
			line = get_str(file);
			strsplit(tab, line, " ");
			if (tab.size() != 0)
			{
				if (tab[0] == "v")
					add_point(Vector3(stof(tab[1]), stof(tab[2]), stof(tab[3])), tmp_part_index);
				else if (tab[0] == "vt")
					add_uv(Vector2(stof(tab[1]), 1.0f - stof(tab[2])), tmp_part_index);
				else if (tab[0] == "vn")
					add_normale(Vector3(stof(tab[1]), stof(tab[2]), stof(tab[3])), tmp_part_index);
				else if (tab[0] == "o")
				{
					add_new_part((tab.size() == 2 ? tab[1] : "Unnamed"));
					tmp_part_index++;
				}
				else if (tab[0] == "mtllib")
				{
					jgl::String to_send = address + tab[1];
					parse_materials(to_send);
				}
				else if (tab[0] == "usemtl")
				{
					Material* tmp_material = find_material(tab[1]);
					_parts[tmp_part_index]->set_material(tmp_material);
				}
				else if (tab[0] == "f")
				{
					if (tab.size() == 4)
					{
						compose_face(this, tab, 0, color, tmp_part_index);
					}
					else
					{
						compose_face(this, tab, 0, color, tmp_part_index);
						compose_face(this, tab, 1, color, tmp_part_index);
					}
					//else
					//	error_exit(1, "Error while parsing a mesh : facee with strange number of index\nLine = " + line);
				}
			}
		}
		bake();
	}

	void Mesh::compute_axis()
	{
		float tmp_yaw = degree_to_radian(_rotation.y);
		float tmp_pitch = degree_to_radian(_rotation.z);

		_rot_matrix = Matrix4x4(Matrix_type::rotation, _rotation);
		_rot_matrix.value[3][3] = 1.0f;
		_forward = (Vector3(sin(tmp_yaw - 3.14f / 2.0f), 0.0f, cos(tmp_yaw - 3.14f / 2.0f))).normalize();
		_right = (Vector3(cos(tmp_pitch) * sin(tmp_yaw), sin(tmp_pitch), cos(tmp_pitch) * cos(tmp_yaw))).normalize();
		_up = ((_forward).cross(_right)).normalize();
	}

	void Mesh::look_at(Vector3 target)
	{
		Vector3	result;

		result = (_pos - target).normalize();
		_rotation.y = radian_to_degree(atan2(result.z, -result.x)) - 90;
		_rotation.z = radian_to_degree(atan2(result.y,
			sqrt(result.x * result.x + result.z * result.z)));
		_rotation.z = clamp_float(-89, _rotation.z, 89);
		compute_axis();
	}

	void Mesh::rotate_around_point(Vector3 target, Vector3 delta)
	{
		Vector3 tmp;
		Matrix4x4 rotation;

		rotation = Matrix4x4(Matrix_type::rotation, delta.x, delta.y, delta.z);

		tmp = _pos - target;
		tmp = rotation * tmp;
		_pos = tmp + target;
	}

	void Mesh::rotate(Vector3 delta)
	{
		_rotation += delta;
		compute_axis();
	}

	void Mesh::compute_bubble_box()
	{
		Vector3 total;
		size_t total_size;

		total = 0;
		total_size = 0;
		for (size_t j = 0; j < _parts.size(); j++)
		{
			Mesh_part* tmp = check_part(j);
			for (size_t i = 0; i < tmp->vertices().size(); i++)
			{
				total += tmp->vertices()[i];
				total_size++;
			}
		}
		_center = total / total_size;
		_radius = 0;
		for (size_t j = 0; j < _parts.size(); j++)
		{
			Mesh_part* tmp = check_part(j);
			for (size_t i = 0; i < tmp->vertices().size(); i++)
			{
				float tmp_radius = _center.distance(tmp->vertices()[i]);
				if (_radius < tmp_radius)
					_radius = tmp_radius;
			}
		}
	}

	void Mesh::bake()
	{
		for (size_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->bake(_rot_matrix);
		}
	}

	void Mesh::render_differed(Camera* camera, Vector3 p_pos)
	{
		for (size_t i = 0; i < _parts.size(); i++)
			_parts[i]->render(this, camera, p_pos);
	}

void Mesh::add_component(Mesh* mesh, Vector3 p_pos, int index)
{
	for (size_t tmp_index = 0; tmp_index < mesh->parts().size(); tmp_index++)
	{
		Mesh_part* tmp = check_part((index < 0 ? -1 : index + tmp_index));
		Mesh_part* other = mesh->check_part(tmp_index);
		size_t index_actual_vertices;
		size_t index_actual_uvs;
		size_t index_actual_normales;

		index_actual_vertices = tmp->vertices().size();
		index_actual_uvs = tmp->uvs().size();
		index_actual_normales = tmp->normales().size();

		for (size_t i = 0; i < other->vertices().size(); i++)
			add_point(other->vertices()[i] + p_pos);
		for (size_t i = 0; i < other->uvs().size(); i++)
			add_uv(other->uvs()[i]);
		for (size_t i = 0; i < other->normales().size(); i++)
			add_normale(other->normales()[i]);

		for (size_t i = 0; i < other->faces().size(); i++)
		{
			Face* actual;

			actual = other->faces(i);
			add_face(Face(new int[3]{
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
				}), (index == -1 ? -1 : index + tmp_index));
		}
	}	
}

	Mesh_part* Mesh::check_part(int index)
	{
		if (index < 0)
			index = 0;
		if (static_cast<size_t>(index) >= _parts.size())
		{
			Mesh_part* tmp = new Mesh_part();
			_parts.push_back(tmp);
		}
		return (_parts[index]);
	}

	Mesh_part* Mesh::control_part(int index)
	{
		if (index < 0)
			index = 0;
		if (static_cast<size_t>(index) >= _parts.size())
			error_exit(1, "Bad index in control_part");
		return (_parts[index]);
	}

	bool Mesh::remove_part(Mesh_part* p_part)
	{
		for (size_t i = 0; i < _parts.size(); i++)
		{
			if (p_part == _parts[i])
			{
				_parts.erase(_parts.begin() + i);
				return (true);
			}
		}
		return (false);
	}
	bool Mesh::remove_part(jgl::String p_name)
	{
		for (size_t i = 0; i < _parts.size(); i++)
		{
			if (_parts[i]->name() == p_name)
			{
				_parts.erase(_parts.begin() + i);
				return (true);
			}
		}
		return (false);
	}

	void Mesh::add_point(Vector3 p_point, int index)
	{
		Mesh_part* tmp = check_part(index);
		tmp->add_point(p_point);
	}

	void Mesh::add_uv(Vector2 p_uv, int index)
	{
		Mesh_part* tmp = check_part(index);
		tmp->add_uv(p_uv);
	}

	void Mesh::add_normale(Vector3 p_normale, int index)
	{
		Mesh_part* tmp = check_part(index);
		tmp->add_normale(p_normale);
	}

	void Mesh::add_face(Face p_face, int index)
	{
		Mesh_part* tmp = check_part(index);
		tmp->add_face(p_face);
	}

	void Mesh::set_diffuse_texture(Image* p_texture, int index)
	{
		if (index == -1)
		{
			if (_parts.size() == 0)
				add_new_part();
			for (size_t i = 0; i < _parts.size(); i++)
			{
				if (_parts[i]->material() == jgl_base_material)
					_parts[i]->set_material(new Material(*jgl_base_material));
				_parts[i]->material()->diffuse_texture = p_texture;
			}
		}
		else
		{
			Mesh_part* tmp = check_part(index);
			if (tmp->material() == jgl_base_material)
				tmp->set_material(new Material(*jgl_base_material));
			tmp->material()->diffuse_texture = p_texture;
		}
	}

	void Mesh::set_diffuse_texture(Sprite_sheet* p_texture, int index)
	{
		if (p_texture != nullptr)
			set_diffuse_texture(p_texture->image(), index);
	}

	void Mesh::clear()
	{
		_rotation = 0;
		for (size_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->clear();
		}
	}
	void Mesh::clear_baked()
	{
		for (size_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->clear_baked();
		}
	}
}