#ifndef JGL_MESH_H
#define JGL_MESH_H

namespace jgl
{
	struct Face
	{
		Color color;
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
			color = Color(255, 255, 255);
		}
		Face(int p_index_vertices[3], int p_index_uvs[3], int p_index_normale[3], Color p_color = Color(190, 190, 190))
		{
			normale = 0;
			for (size_t i = 0; i < 3; i++)
			{
				index_vertices[i] = p_index_vertices[i];
				index_uvs[i] = p_index_uvs[i];
				index_normale[i] = p_index_normale[i];
			}
			color = p_color;
		}
	};

	class Mesh
	{
	protected:
		GLuint _vertex_buffer;
		GLuint _color_buffer;
		GLuint _uv_buffer;
		GLuint _normale_buffer;
		GLuint _alpha_buffer;

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

		std::vector<Face>	_faces;

		std::vector<Vector3>	_vertices;
		std::vector<Vector2>	_uvs;
		std::vector<Vector3>	_normales;

		float _transparency;

		std::vector<Vector3>	_baked_vertices;
		std::vector<Vector2>	_baked_uvs;
		std::vector<Color>	_baked_colors;
		std::vector<Vector3>	_baked_normales;

		Image* _texture;

	public:
		Mesh(Vector3 p_pos, Vector3 p_rot = 0, Vector3 p_size = 1);
		Mesh(jgl::String path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color = Color(190, 190, 190));

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

		std::vector<Vector3>& vertices() { return (_vertices); }
		std::vector<Vector2>& uvs() { return (_uvs); }
		std::vector<Vector3>& normales() { return (_normales); }
		std::vector<Face>& faces() { return (_faces); }
		Face* faces(size_t i) { if (i >= _faces.size())return (NULL); return (&(_faces[i])); }

		void add_component(Mesh* mesh) { add_component(mesh, mesh->pos()); }
		void add_component(Mesh* mesh, Vector3 pos);
		void add_point(Vector3 p_point) { _vertices.push_back(p_point); }
		void add_uv(Vector2 p_uv) { _uvs.push_back(p_uv); }
		void add_normale(Vector3 p_normale) { _normales.push_back(p_normale); }
		void add_face(Face p_face) { _faces.push_back(p_face); }
		void set_texture(Image* p_texture) { _texture = p_texture; }
		void set_texture(Sprite_sheet* p_texture) { if (p_texture == nullptr)_texture = nullptr;else set_texture(p_texture->image()); }
		void set_transparency(float p_transparency) { _transparency = p_transparency; }
		void compute_normales();
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

		void render_color(Camera* camera) { render_color_differed(camera, pos()); }
		void render_texture(Camera* camera) { render_texture_differed(camera, pos()); }
		void render_color_differed(Camera* camera, Vector3 p_pos);
		void render_texture_differed(Camera* camera, Vector3 p_pos);
		void render(Camera* camera) { render_differed(camera, pos()); }
		void render_differed(Camera* camera, Vector3 p_pos);
	};
	Mesh *primitive_cube(Vector3 pos, Vector3 rot, Vector3 size, jgl::Color color, bool should_bake = true);

	Mesh *primitive_voxel(Vector3 pos, Sprite_sheet *tileset, Vector2 top_sprite, Vector2 side_sprite, Vector2 down_sprite, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
	Mesh *primitive_voxel(Vector3 pos, Sprite_sheet *tileset, size_t type, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
	Mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector2 size, jgl::Color color, bool should_bake = true);
	Mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector3 size, jgl::Color color, bool should_bake = true);
}

#endif
