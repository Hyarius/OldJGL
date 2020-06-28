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
		Material(jgl::String p_name)
		{
			if (_empty_texture == nullptr)
				_empty_texture = new Image(1, 1, Color(255, 255, 255));
			name = p_name;
			ambiant_texture = empty_texture();
			normal_texture = empty_texture();
			diffuse_texture = empty_texture();
			specular_texture = empty_texture();
			specular_hight_light = empty_texture();
			alpha_texture = empty_texture();
			bump = empty_texture();
		}
		~Material()
		{
			if (ambiant_texture != empty_texture())
				delete ambiant_texture;
			if (normal_texture != empty_texture())
				delete normal_texture;
			if (diffuse_texture != empty_texture())
				delete diffuse_texture;
			if (specular_texture != empty_texture())
				delete specular_texture;
			if (specular_hight_light != empty_texture())
				delete specular_hight_light;
			if (alpha_texture != empty_texture())
				delete alpha_texture;
			if (bump != empty_texture())
				delete bump;
		}
	};


	struct Face
	{
		Vector3 normale;
		int index_vertices[3];
		int index_uvs[3];
		int index_normale[3];

		Face()
		{
			normale = 0;
			index_vertices[0] = 0;
			index_uvs[0] = 0;
			index_normale[0] = 0;
		}
		Face(int p_index_vertices[3], int p_index_uvs[3], int p_index_normale[3])
		{
			normale = 0;
			for (size_t i = 0; i < 3; i++)
			{
				index_vertices[i] = p_index_vertices[i];
				index_uvs[i] = p_index_uvs[i];
				index_normale[i] = p_index_normale[i];
			}
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

		jgl::Array<Vector3>	_vertices;
		jgl::Array<Vector2>	_uvs;
		jgl::Array<Vector3>	_normales;

		jgl::Array<Vector3>	_baked_vertices;
		jgl::Array<Vector2>	_baked_uvs;
		jgl::Array<Vector3>	_baked_normales;

		Material* _material;

	public:
		static void set_base_material(Material* p_material) { _base_material = p_material;}
		static Material* base_material() { return (_base_material); }
		Mesh_part(jgl::String p_name = "unnamed");

		jgl::String name() { return (_name); }

		jgl::Array<Vector3>& vertices() { return (_vertices); }
		void set_vertices(jgl::Array<Vector3>& p_vertice) { _vertices = p_vertice;	}
		Vector3 vertices(size_t index) { if (index >= _vertices.size())return (-1); return (_vertices[index]); }

		jgl::Array<Vector2>& uvs() { return (_uvs); }
		void set_uvs(jgl::Array<Vector2>& p_uvs) { _uvs = p_uvs; }
		Vector2 uvs(size_t index) { if (index >= _uvs.size())return (-1); return (_uvs[index]); }

		jgl::Array<Vector3>& normales() { return (_normales); }
		void set_normales(jgl::Array<Vector3>& p_normale) { _normales = p_normale; }
		Vector3 normales(size_t index) { if (index >= _normales.size())return (-1); return (_normales[index]); }

		jgl::Array<Face>& faces() { return (_faces); }
		Face* faces(size_t i) { if (i >= _faces.size())return (NULL); return (&(_faces[i])); }
		Material* material() { return (_material); }

		void set_name(jgl::String p_name) { _name = p_name; }
		void add_point(Vector3 p_point) { _vertices.push_back(p_point); }
		void add_uv(Vector2 p_uv) { _uvs.push_back(p_uv); }
		void add_normale(Vector3 p_normale) { _normales.push_back(p_normale); }
		void add_face(Face p_face) { _faces.push_back(p_face); }
		void set_material(Material* p_material) { if (p_material == nullptr)_material = _base_material;else _material = p_material; }
		void compute_normales(jgl::Matrix4x4 rot_matrix);

		void bake(jgl::Matrix4x4 rot_matrix);
		void clear();
		void clear_baked();

		void render_color(class Mesh* parent, Camera* camera, Vector3 p_pos);
		void render_texture(class Mesh* parent, Camera* camera, Vector3 p_pos);
		void render(class Mesh *parent, Camera* camera, Vector3 p_pos);
	};

	class Mesh
	{
	protected:
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

		jgl::Array<Material*> _materials;
		jgl::Array<Mesh_part*> _parts;

	public:
		static void set_base_material(Material* p_material) { _base_material = p_material; Mesh_part::set_base_material(p_material); };
		static void delete_base_material() { if (_base_material != nullptr)delete _base_material; _base_material = nullptr; Mesh_part::set_base_material(nullptr);}
		static Material* base_material() { if (_base_material == nullptr)set_base_material(new Material("No material")); return (_base_material); }
		Mesh(Vector3 p_pos, Vector3 p_rot = 0, Vector3 p_size = 1);
		Mesh(jgl::String path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color = Color(190, 190, 190));
		~Mesh();
		float transparency() { return (_transparency); }
		bool kinetic() { return (_kinetic); }
		Vector3 pos() { return (_pos); }
		float radius() { return (_radius); }
		Vector3 center() { return (_center); }
		Vector3 velocity() { return (_velocity); }
		Vector3 size() { return (_size); }
		Vector3 rotation() { return (_rotation); }
		Matrix4x4 rot_matrix() { return (_rot_matrix); }
		Vector3 forward() { return (_forward); }
		Vector3 right() { return (_right); }
		Vector3 up() { return (_up); }

		Material* find_material(jgl::String name);
		Material* material(size_t index = 0) { if (index >= _materials.size())return (nullptr); return (_materials[index]); }

		jgl::Array<Mesh_part*>& parts() { return (_parts); }
		Mesh_part* parts(size_t index) { if (index >= _parts.size())return (nullptr); return (_parts[index]); }
		Mesh_part* check_part(int index);
		Mesh_part* control_part(int index);

		void parse_materials(jgl::String p_path);
		void add_material(Material* p_material) { _materials.push_back(p_material); }
		void add_part(Mesh_part* p_part) { _parts.push_back(p_part); }
		bool remove_part(Mesh_part* p_part);
		bool remove_part(jgl::String p_name);
		void add_new_part(jgl::String p_name = "unnamed") { add_part(new Mesh_part(p_name)); }
		void add_component(Mesh* mesh, int index = -1) { add_component(mesh, mesh->pos(), index); }
		void add_component(Mesh* mesh, Vector3 pos, int index = -1);
		void add_point(Vector3 p_point, int index = -1);
		void add_uv(Vector2 p_uv, int index = -1);
		void add_normale(Vector3 p_normale, int index = -1);
		void add_face(Face p_face, int index = -1);

		void set_vertices(jgl::Array<Vector3>& p_vertices, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_vertices(p_vertices); }
		void set_uvs(jgl::Array<Vector2>& p_uvs, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_uvs(p_uvs); }
		void set_normales(jgl::Array<Vector3>& p_normales, int index = -1) { Mesh_part* tmp = check_part(index); tmp->set_normales(p_normales); }

		void set_diffuse_texture(Image* p_texture, int index = -1);
		void set_diffuse_texture(Sprite_sheet* p_texture, int index = -1);
		void set_transparency(float p_transparency) { _transparency = p_transparency; }
		void compute_bubble_box();
		void compute_axis();

		void set_kinetic(bool p_kinetic) { _kinetic = p_kinetic; }

		void bake();
		void clear();
		void clear_baked();

		void look_at(Vector3 target);
		void rotate_around_point(Vector3 target, Vector3 delta);
		void rotate(Vector3 delta);
		void set_rotation(Vector3 p_rot) { _rotation = p_rot; compute_axis(); }
		void move(Vector3 delta) { _pos += delta; }
		void add_velocity(Vector3 delta) { _velocity += delta; }
		void apply_velocity() { move(_velocity); }
		void reset_velocity() { _velocity = 0; }
		void set_velocity(Vector3 p_velocity) { _velocity = p_velocity; }
		void place(Vector3 p_pos) { _pos = p_pos; }

		void render(Camera* camera) { render_differed(camera, pos()); }
		void render_differed(Camera* camera, Vector3 p_pos);
	};
	Mesh *primitive_cube(Vector3 pos, Vector3 rot, Vector3 size, jgl::Color color, bool should_bake = true);

	Mesh *primitive_voxel(Vector3 pos, Sprite_sheet *tileset, Vector2 top_sprite, Vector2 side_sprite, Vector2 down_sprite, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
	Mesh *primitive_voxel(Vector3 pos, Sprite_sheet *tileset, size_t type, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
}


std::ostream& operator<<(std::ostream& os, jgl::Face to_print);
std::ostream& operator<<(std::ostream& os, jgl::Material to_print);

#endif
