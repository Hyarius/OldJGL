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

	void tmp_strsplit(jgl::Array<jgl::String>& tab, jgl::String& input, jgl::Glyph& delim, bool regroup = true)
	{
		uint32_t tmp = input.size();
		uint32_t index = 0;
		uint32_t nb_word = 0;

		tab.resize(count_word(input, delim));
		while (index < tmp)
		{
			uint32_t word_len = count_word_len(input, delim, index);
			if (word_len != 0 || regroup == true)
			{
				tab[nb_word].clear();
				input.substr(tab[nb_word], index, index + word_len);
				nb_word++;
			}
			index += word_len + 1;
		}
	}

	static void compose_face(jgl::Mesh *target, jgl::Array<jgl::String>& tab, int type, Color color, uint32_t index)
	{
		static jgl::Array<jgl::String> face_content;
		static jgl::Glyph delim = '/';
		int index_vertices[3] = { -1, -1, -1 }, index_uvs[3] = { -1, -1, -1 }, index_normales[3] = { -1, -1, -1 };
		int delta_vertice_index = 0;
		int delta_uvs_index = 0;
		int delta_normale_index = 0;

		for (uint32_t i = 0; i < index; i++)
		{
			Mesh_part* tmp = target->parts(i);
			if (tmp == nullptr)
				error_exit(1, "No part inside mesh");
			delta_vertice_index += tmp->vertices().size();
			delta_uvs_index += tmp->uvs().size();
			delta_normale_index += tmp->normales().size();
		}

		for (uint32_t i = 0; i < 3; i++)
		{
			tmp_strsplit(face_content, tab[face_index_value[type][i]], delim, true);
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
		jgl::Array<jgl::String> tab;
		static jgl::Glyph delim = '/';
			
		tmp_strsplit(tab, path, delim);

		jgl::String result = "";

		for (uint32_t i = 0; i < tab.size() - 1; i++)
		{
			result += tab[i];
			result += "/";
		}

		return (result);
	}

	jgl::Color create_color_from_tab(jgl::Array<jgl::String>& tab)
	{
		return (Color(stof(tab[1]), stof(tab[2]), stof(tab[3])));
	}

	void Mesh::parse_materials(jgl::String p_path)
	{
		Material* material = nullptr;
		std::fstream file = open_file(p_path, std::ios_base::in | std::ios_base::out);
		jgl::String line;
		static jgl::Glyph delim = ' ';
		static jgl::String controler[17] = {
			"newmtl",
			"Ka",
			"Kd",
			"Ks",
			"Ns",
			"Ke",
			"Ni",
			"d",
			"illum",
			"map_Ka",
			"map_Kd",
			"map_Ks",
			"map_Ns",
			"map_d",
			"map_Bump",
			"map_bump",
			"bump"
		};
		static jgl::Array<jgl::String> tab;
		jgl::String address = create_address(p_path);

		while (file.eof() == false)
		{
			line = get_str(file);
			if (line.size() != 0 && line[0] != '#')
			{
				tab.clear();
				tmp_strsplit(tab, line, delim, false);
				if (tab[0].equal(controler[0]) == true)
				{
					if (material != nullptr)
						_materials.push_back(material);
					material = new Material(tab[1]);
				}
				// Ambient Color
				else if (tab[0].equal(controler[1]) == true)
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ka construction");
					if (material == nullptr)
						material = new Material("Unnamed");
					material->ka = create_color_from_tab(tab);
				}
				// Diffuse Color
				else if (tab[0].equal(controler[2]) == true)
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Kd construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->kd = create_color_from_tab(tab);
				}
				// Specular Color
				else if (tab[0].equal(controler[3]) == true)
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ks construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->ks = create_color_from_tab(tab);
				}
				// Specular Exponent
				else if (tab[0].equal(controler[4]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in Ns construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->ns = stof(tab[1]);
				}
				else if (tab[0].equal(controler[5]) == true)
				{
					if (tab.size() != 4)
						error_exit(1, "Bad number of argument in Ke construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->ke = create_color_from_tab(tab);
				}
				// Optical Density
				else if (tab[0].equal(controler[6]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in Ni construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->ni = stof(tab[1]);
				}
				// Dissolve
				else if (tab[0].equal(controler[7]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in D construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->d = stof(tab[1]);
				}
				// Illumination
				else if (tab[0].equal(controler[8]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in illum construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->illum = stoi(tab[1]);
				}
				// Ambient Texture Map
				else if (tab[0].equal(controler[9]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ka construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->ambiant_texture = new Image(tab[1]);
				}
				// Diffuse Texture Map
				else if (tab[0].equal(controler[10]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Kd construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->diffuse_texture = new Image(address + tab[1]);
				}
				// Specular Texture Map
				else if (tab[0].equal(controler[11]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ks construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->specular_texture = new Image(address + tab[1]);
				}
				// Specular Hightlight Map
				else if (tab[0].equal(controler[12]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Ns construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->specular_hight_light = new Image(address + tab[1]);
				}
				// Alpha Texture Map
				else if (tab[0].equal(controler[13]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in map Kd construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->alpha_texture = new Image(address + tab[1]);
				}
				// Bump Map
				else if (tab[0].equal(controler[14]) == true || tab[0].equal(controler[15]) == true || tab[0].equal(controler[16]) == true)
				{
					if (tab.size() != 2)
						error_exit(1, "Bad number of argument in bump map construction");

					if (material == nullptr)
						material = new Material("Unnamed");
					material->bump = new Image(address + tab[1]);
				}

			}
		}
		if (material != nullptr)
			_materials.push_back(material);
	}

	Material* Mesh::find_material(jgl::String p_name)
	{
		for (uint32_t i = 0; i < _materials.size(); i++)
		{
			if (_materials[i]->name == p_name)
				return (_materials[i]);
		}
		return (base_material());
	}

	Mesh::Mesh(jgl::String p_path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color) : Mesh(p_pos, p_rot, p_size)
	{
		int tmp_part_index = -1;
		jgl::String line;
		static jgl::Glyph delim = ' ';
		static jgl::String controler[7] = {
			"v",
			"vt",
			"vn",
			"o",
			"mtllib",
			"usemtl",
			"f"
		};
		static jgl::Array<jgl::String> tab;
		std::fstream file = open_file(p_path, std::ios_base::in | std::ios_base::out);
		jgl::String address = create_address(p_path);

		while (file.eof() == false)
		{
			line = get_str(file);
			if (line.size() != 0)
			{
				tab.clear();
				tmp_strsplit(tab, line, delim, false);

				if (tab.size() != 0)
				{
					if (tab[0].equal(controler[0]) == true)
						add_point(Vector3(stof(tab[1]), stof(tab[2]), stof(tab[3])), tmp_part_index);
					else if (tab[0].equal(controler[1]) == true)
						add_uv(Vector2(stof(tab[1]), 1.0f - stof(tab[2])), tmp_part_index);
					else if (tab[0].equal(controler[2]) == true)
						add_normale(Vector3(stof(tab[1]), stof(tab[2]), stof(tab[3])), tmp_part_index);
					else if (tab[0].equal(controler[3]) == true)
					{
						add_new_part((tab.size() == 2 ? tab[1] : "Unnamed"));
						tmp_part_index++;
					}
					else if (tab[0].equal(controler[4]) == true)
					{
						jgl::String to_send = address + tab[1];
						parse_materials(to_send);
					}
					else if (tab[0].equal(controler[5]) == true)
					{
						Material* tmp_material = find_material(tab[1]);
						check_part(tmp_part_index)->set_material(tmp_material);
					}
					else if (tab[0].equal(controler[6]) == true)
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
		}
		bake();
	}
	Mesh::~Mesh()
	{
		for (uint32_t i = 0; i < _materials.size(); i++)
		{
			if (_materials[i] != Mesh::base_material())
				delete _materials[i];
		}
		for (uint32_t i = 0; i < _parts.size(); i++)
			delete _parts[i];
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

	void Mesh::resize(Vector3 p_size)
	{
		_size = p_size;
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

	void Mesh::rotate_around_point(Vector3 target, float angle, Vector3 axis)
	{
		Vector3 tmp;
		Matrix4x4 rotation = jgl::Matrix4x4::matrix_custom_rotation(angle, axis);

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
		uint32_t total_size;

		total = 0;
		total_size = 0;
		for (uint32_t j = 0; j < _parts.size(); j++)
		{
			Mesh_part* tmp = check_part(j);
			for (uint32_t i = 0; i < tmp->vertices().size(); i++)
			{
				total += tmp->vertices()[i];
				total_size++;
			}
		}
		_center = total / total_size;
		_radius = 0;
		for (uint32_t j = 0; j < _parts.size(); j++)
		{
			Mesh_part* tmp = check_part(j);
			for (uint32_t i = 0; i < tmp->vertices().size(); i++)
			{
				float tmp_radius = _center.distance(tmp->vertices()[i]);
				if (_radius < tmp_radius)
					_radius = tmp_radius;
			}
		}
	}

	void Mesh::bake()
	{
		for (uint32_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->bake(_rot_matrix);
		}
	}

	void Mesh::render_differed(const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport)
	{
		for (uint32_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->render(this, camera, p_pos, viewport);
		}
	}

void Mesh::add_component(const Mesh* mesh, const Vector3 p_pos, const int index)
{
	for (uint32_t tmp_index = 0; tmp_index < mesh->parts().size(); tmp_index++)
	{
		Mesh_part* tmp = check_part((index < 0 ? -1 : index + tmp_index));
		Mesh_part* other = mesh->control_part(tmp_index);
		uint32_t index_actual_vertices;
		uint32_t index_actual_uvs;
		uint32_t index_actual_normales;

		index_actual_vertices = tmp->vertices().size();
		index_actual_uvs = tmp->uvs().size();
		index_actual_normales = tmp->normales().size();

		for (uint32_t i = 0; i < other->vertices().size(); i++)
			add_point(other->vertices()[i] + p_pos);
		for (uint32_t i = 0; i < other->uvs().size(); i++)
			add_uv(other->uvs()[i]);
		for (uint32_t i = 0; i < other->normales().size(); i++)
			add_normale(other->normales()[i]);

		for (uint32_t i = 0; i < other->faces().size(); i++)
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
		if (static_cast<uint32_t>(index) >= _parts.size())
		{
			Mesh_part* tmp = new Mesh_part();
			_parts.push_back(tmp);
		}
		return (_parts[index]);
	}

	Mesh_part* Mesh::control_part(int index) const
	{
		if (index < 0)
			index = 0;
		if (static_cast<uint32_t>(index) >= _parts.size())
			error_exit(1, "Bad index in control_part");
		return (_parts[index]);
	}

	bool Mesh::remove_part(const Mesh_part* p_part)
	{
		for (uint32_t i = 0; i < _parts.size(); i++)
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
		for (uint32_t i = 0; i < _parts.size(); i++)
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

	void Mesh::clear()
	{
		_rotation = 0;
		for (uint32_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->clear();
		}
	}
	void Mesh::clear_baked()
	{
		for (uint32_t i = 0; i < _parts.size(); i++)
		{
			_parts[i]->clear_baked();
		}
	}
}