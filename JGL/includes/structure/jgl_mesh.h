#ifndef JGL_MESH_H
#define JGL_MESH_H

namespace jgl
{
	struct Material
	{
	private:
		static Image* _empty_texture;// new const Image(1, 1, Color(255, 255, 255));
	public:
		jgl::String name;

		Color ka = Color(255, 255, 255);
		Color kd = Color(180, 180, 180);
		Color ks = Color(0, 0, 0);
		Color ke = ka;
		float ns = 1;
		float ni = 1;
		float d = 1;
		int illum = 2;
		jgl::Image* ambiant_texture = empty_texture();
		jgl::Image* normal_texture = empty_texture();
		jgl::Image* diffuse_texture = empty_texture();
		jgl::Image* specular_texture = empty_texture();
		jgl::Image* specular_hight_light = empty_texture();
		jgl::Image* alpha_texture = empty_texture();
		jgl::Image* bump = empty_texture();

		static Image* empty_texture() { return (_empty_texture); }
		static void delete_empty_texture() { if (_empty_texture != nullptr)delete _empty_texture; _empty_texture = nullptr; }
		Material(const jgl::String p_name);
		~Material();

		friend std::ostream& operator<<(std::ostream& os, const jgl::Material to_print)
		{
			os << "Material : " << to_print.name << std::endl;
			os << "		ka : " << to_print.ka << std::endl;
			os << "		kd : " << to_print.kd << std::endl;
			os << "		ks : " << to_print.ks << std::endl;
			os << "		ke : " << to_print.ke << std::endl;
			os << "		ns : " << to_print.ns << std::endl;
			os << "		ni : " << to_print.ni << std::endl;
			os << "		d : " << to_print.d << std::endl;
			os << "		illum : " << to_print.illum << std::endl;
			if (to_print.ambiant_texture != nullptr)
				os << "		ambiant texture : " << to_print.ambiant_texture->path() << std::endl;
			if (to_print.diffuse_texture != nullptr)
				os << "		diffuse texture : " << to_print.diffuse_texture->path() << std::endl;
			if (to_print.specular_texture != nullptr)
				os << "		specular texture : " << to_print.specular_texture->path() << std::endl;
			if (to_print.specular_hight_light != nullptr)
				os << "		specular hight light : " << to_print.specular_hight_light->path() << std::endl;
			if (to_print.alpha_texture != nullptr)
				os << "		alpha texture : " << to_print.alpha_texture->path() << std::endl;
			if (to_print.bump != nullptr)
				os << "		bump map : " << to_print.bump->path() << std::endl;

			return (os);
		}
	};


	struct Face
	{
		//Vector3 normale;
		int index_vertices[3];
		int index_uvs[3];
		int index_normale[3];

		Face()
		{
			//normale = 0;
			index_vertices[0] = 0;
			index_uvs[0] = 0;
			index_normale[0] = 0;
		}
		Face(const int p_index_vertices[3], const int p_index_uvs[3], const int p_index_normale[3])
		{
			//normale = 0;
			for (uint32_t i = 0; i < 3; i++)
			{
				index_vertices[i] = p_index_vertices[i];
				index_uvs[i] = p_index_uvs[i];
				index_normale[i] = p_index_normale[i];
			}
		}
		Face(const jgl::Array<int> p_index_vertices, const jgl::Array<int> p_index_uvs, const jgl::Array<int> p_index_normale)
		{
			if (p_index_vertices.size() != 3 || p_index_uvs.size() != 3 || p_index_normale.size() != 3)
				error_exit(1, "Bad number of argument in face definition");
			//normale = 0;
			for (uint32_t i = 0; i < 3; i++)
			{
				index_vertices[i] = p_index_vertices[i];
				index_uvs[i] = p_index_uvs[i];
				index_normale[i] = p_index_normale[i];
			}
		}
		friend std::ostream& operator<<(std::ostream& os, const jgl::Face to_print)
		{
			os << "Index vertices : [" << to_print.index_vertices[0] << "][" << to_print.index_vertices[1] << "][" << to_print.index_vertices[2] << "]" << std::endl;
			os << "Index uvs : [" << to_print.index_uvs[0] << "][" << to_print.index_uvs[1] << "][" << to_print.index_uvs[2] << "]" << std::endl;
			os << "Index normales : [" << to_print.index_normale[0] << "][" << to_print.index_normale[1] << "][" << to_print.index_normale[2] << "]" << std::endl;

			return (os);
		}
	};

	class Mesh_part
	{
	protected:
		static Material* _base_material;
		jgl::String _name;

		GLuint _vertex_buffer;
		GLuint _uv_buffer;
		GLuint _normale_buffer;

		jgl::Array<Face>	_faces;

		jgl::share_object< jgl::Array<Vector3> > _vertices;
		jgl::share_object< jgl::Array<Vector2> > _uvs;
		jgl::share_object< jgl::Array<Vector3> > _normales;

		jgl::Array<Vector3> _baked_vertices;
		jgl::Array<Vector2> _baked_uvs;
		jgl::Array<Vector3> _baked_normales;

		Material* _material;

	public:
		static void set_base_material(Material* p_material) { _base_material = p_material;}
		static Material* base_material() { return (_base_material); }
		Mesh_part(const jgl::String p_name = "unnamed");
		const jgl::String name() const { return (_name); }

		jgl::Array<Vector3>& vertices() { return (*_vertices); }
		const jgl::Array<Vector3>& vertices() const { return (*_vertices); }
		void set_vertices(jgl::Array<Vector3>& p_vertice) { *_vertices = p_vertice; }
		void set_vertices(jgl::share_object<jgl::Array<Vector3>> p_vertice) { _vertices = p_vertice;	}
		const Vector3 vertices(const uint32_t index) const { if (index >= _vertices->size())return (-1); return (_vertices->operator[](index)); }

		jgl::Array<Vector2>& uvs() { return (*_uvs); }
		const jgl::Array<Vector2>& uvs() const { return (*_uvs); }
		void set_uvs(jgl::Array<Vector2>& p_uvs) { *_uvs = p_uvs; }
		void set_uvs(jgl::share_object < jgl::Array<Vector2>> p_uvs) { _uvs = p_uvs; }
		const Vector2 uvs(const uint32_t index) const { if (index >= _uvs->size())return (-1); return (_uvs->operator[](index)); }

		jgl::Array<Vector3>& normales() { return (*_normales); }
		const jgl::Array<Vector3>& normales() const { return (*_normales); }
		void set_normales(jgl::Array<Vector3>& p_normale) { *_normales = p_normale; }
		void set_normales(jgl::share_object < jgl::Array<Vector3> > p_normale) { _normales = p_normale; }
		const Vector3 normales(const uint32_t index) const { if (index >= _normales->size())return (-1); return (_normales->operator[](index)); }

		jgl::Array<Face>& faces() { return (_faces); }
		const jgl::Array<Face>& faces() const { return (_faces); }
		Face* faces(uint32_t i) { if (i >= _faces.size())return (NULL); return (&(_faces[i])); }
		const Material* material() const { return (_material); }

		void set_name(const jgl::String p_name) { _name = p_name.copy(); }
		void add_point(Vector3 p_point) { _vertices->push_back(p_point); }
		void add_uv(Vector2 p_uv) { _uvs->push_back(p_uv); }
		void add_normale(Vector3 p_normale) { _normales->push_back(p_normale); }
		void add_face(Face p_face) { _faces.push_back(p_face); }
		void set_material(Material* p_material) { if (p_material == nullptr)_material = _base_material;else _material = p_material; }
		void compute_normales(const jgl::Matrix4x4 rot_matrix);

		void bake(jgl::Matrix4x4 rot_matrix);
		void clear();
		void clear_baked();

		void render_color(const class Mesh* parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport = nullptr);
		void render_texture(const class Mesh* parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport = nullptr);
		void render(const class Mesh *parent, const Camera* camera, Vector3 p_pos, const jgl::Viewport* viewport = nullptr);
	};

	class Mesh
	{
	protected:
		void self_set_material(jgl::Array<jgl::Material*>& p_array, jgl::Material* p_material)
		{
			if (p_array.find(p_material) == p_array.end())
				p_array.push_back(p_material);
			for (uint32_t i = 0; i < _parts.size(); i++)
			{
				Mesh_part* tmp = check_part(i);
				tmp->set_material(p_material);
			}
		}
		void self_set_material(jgl::Array<jgl::Material*>& p_array, jgl::Material* p_material, int index)
		{
			if (p_array.find(p_material) == p_array.end())
				p_array.push_back(p_material);
			Mesh_part* tmp = check_part(index);
			tmp->set_material(p_material);
		}

		static Material* _base_material;

		Vector3 _pos;
		Vector3 _center;
		float _radius;
		Vector3 _size;
		Vector3 _velocity;
		bool _kinetic;

		Vector3 _rotation;
		Matrix4x4 _rot_matrix;
		Vector3 _forward;
		Vector3 _right;
		Vector3 _up;

		float _transparency;

		jgl::Array<Material*> _shared_materials;
		jgl::Array<Material*> _materials;
		jgl::Array<Mesh_part*> _parts;

	public:
		static void set_base_material(Material* p_material) { _base_material = p_material; Mesh_part::set_base_material(p_material); };
		static void delete_base_material() { if (_base_material != nullptr)delete _base_material; _base_material = nullptr; Mesh_part::set_base_material(nullptr);}
		static Material* base_material() { if (_base_material == nullptr)set_base_material(new Material("No material")); return (_base_material); }
		Mesh(const Vector3 p_pos, const Vector3 p_rot = 0, const Vector3 p_size = 1);
		Mesh(const jgl::String path, const Vector3 p_pos, const Vector3 p_rot, const Vector3 p_size, const Color color = Color(190, 190, 190));
		~Mesh();
		const float transparency() const { return (_transparency); }
		const bool kinetic() const { return (_kinetic); }
		const Vector3 pos() const { return (_pos); }
		const float radius() const { return (_radius); }
		const Vector3 center() const { return (_center); }
		const Vector3 velocity() const { return (_velocity); }
		const Vector3 size() const { return (_size); }
		const Vector3 rotation() const { return (_rotation); }
		const Matrix4x4 rot_matrix() const { return (_rot_matrix); }
		const Vector3 forward() const { return (_forward); }
		const Vector3 right() const { return (_right); }
		const Vector3 up() const { return (_up); }

		jgl::Array<jgl::Material*>& materials() { return (_materials); }
		const jgl::Array<jgl::Material*>& materials() const { return (_materials); }
		jgl::Material *materials(const uint32_t index) const { if (index >= _materials.size())return (nullptr); return (_materials[index]); }
		jgl::Material* find_material(jgl::String name);

		jgl::Array<jgl::Mesh_part*>& parts() { return (_parts); }
		const jgl::Array<jgl::Mesh_part*>& parts() const { return (_parts); }
		jgl::Mesh_part* parts(const uint32_t index) const { if (index >= _parts.size())return (nullptr); return (_parts[index]); }
		jgl::Mesh_part* check_part(const int index);
		jgl::Mesh_part* control_part(const int index) const;

		void parse_materials(const jgl::String p_path);
		void add_material(Material* p_material) { _materials.push_back(p_material); }
		void add_part(Mesh_part* p_part) { _parts.push_back(p_part); }
		bool remove_part(const Mesh_part* p_part);
		bool remove_part(const jgl::String p_name);
		void add_new_part(const jgl::String p_name = "unnamed") { add_part(new Mesh_part(p_name)); }
		void add_component(const Mesh* mesh, int index = -1) { add_component(mesh, mesh->pos(), index); }
		void add_component(const Mesh* mesh, const Vector3 pos, const int index = -1);
		void add_point(const Vector3 p_point, const int index = -1);
		void add_uv(const Vector2 p_uv, const int index = -1);
		void add_normale(const Vector3 p_normale, const int index = -1);
		void add_face(const Face p_face, const int index = -1);

		void set_vertices(jgl::Array<Vector3>& p_vertices, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_vertices(p_vertices); }
		void set_vertices(jgl::share_object < jgl::Array<Vector3> > p_vertices, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_vertices(p_vertices); }
		void set_uvs(jgl::Array<Vector2>& p_uvs, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_uvs(p_uvs); }
		void set_uvs(jgl::share_object < jgl::Array<Vector2> > p_uvs, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_uvs(p_uvs); }
		void set_normales(jgl::Array<Vector3>& p_normales, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_normales(p_normales); }
		void set_normales(jgl::share_object < jgl::Array<Vector3> > p_normales, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_normales(p_normales); }

		void set_material(jgl::Material* p_material, const bool shared = false)
		{
			if (shared == true)
				self_set_material(_shared_materials, p_material);
			else
				self_set_material(_materials, p_material);
		}
		void set_material(jgl::Material* p_material, const int index, const bool shared = false)
		{
			if (shared == true)
				self_set_material(_shared_materials, p_material, index);
			else
				self_set_material(_materials, p_material, index);
		}
		
		void set_transparency(const float p_transparency) { _transparency = p_transparency; }
		void compute_bubble_box();
		void compute_axis();

		void set_kinetic(const bool p_kinetic) { _kinetic = p_kinetic; }

		void bake();
		void clear();
		void clear_baked();

		void resize(const Vector3 p_size);
		void look_at(const Vector3 target);
		void rotate_around_point(const Vector3 target, const float angle, const Vector3 axis);
		void rotate(const Vector3 delta);
		void set_rotation(const Vector3 p_rot) { _rotation = p_rot; compute_axis(); }
		void move(const Vector3 delta) { _pos += delta; }
		void add_velocity(const Vector3 delta) { _velocity += delta; }
		void apply_velocity() { move(_velocity); }
		void reset_velocity() { _velocity = 0; }
		void set_velocity(const Vector3 p_velocity) { _velocity = p_velocity; }
		void place(const Vector3 p_pos) { _pos = p_pos; }

		void render(const Camera* camera, const jgl::Viewport* viewport = nullptr) { render_differed(camera, pos(), viewport); }
		void render_differed(const Camera* camera, const Vector3 p_pos, const jgl::Viewport* viewport = nullptr);
	};
	Mesh *primitive_cube(const Vector3 pos, const Vector3 rot, const Vector3 size, const jgl::Color color, const bool should_bake = true);
	Mesh *primitive_voxel(const Vector3 pos, const Sprite_sheet *tileset, const Vector2 top_sprite, const Vector2 side_sprite, const Vector2 down_sprite, const float p_transparency = 1.0f, const bool should_bake = false, const Vector3 rot = 0, const Vector3 size = 1);
	Mesh *primitive_voxel(const Vector3 pos, const Sprite_sheet *tileset, const uint32_t type, const float p_transparency = 1.0f, const bool should_bake = false, const Vector3 rot = 0, const Vector3 size = 1);
}

#endif
