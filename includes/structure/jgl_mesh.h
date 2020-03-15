#ifndef JGL_MESH_H
#define JGL_MESH_H

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

class c_mesh
{
private:
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
	Matrix _rot_matrix;
	Vector3 _forward;
	Vector3 _right;
	Vector3 _up;

	vector<Face>	_faces;

	vector<Vector3>	_vertices;
	vector<Vector2>	_uvs;
	vector<Vector3>	_normales;

	float _transparency;

	vector<Vector3>	_baked_vertices;
	vector<Vector2>	_baked_uvs;
	vector<Color>	_baked_colors;
	vector<Vector3>	_baked_normales;

	c_image *_texture;

public:
	c_mesh(Vector3 p_pos, Vector3 p_rot = 0, Vector3 p_size = 1);
	c_mesh(string path, Vector3 p_pos, Vector3 p_rot, Vector3 p_size, Color color = Color(190, 190, 190));

	float transparency(){return (_transparency);}
	bool kinetic(){return (_kinetic);}
	Vector3 pos(){return (_pos);}
	float radius(){return (_radius);}
	Vector3 center(){return (_center);}
	Vector3 velocity(){return (_velocity);}
	Vector3 size(){return (_size);}
	Vector3 rotation(){return (_rotation);}
	Matrix rot_matrix(){return (_rot_matrix);}
	Vector3 forward(){return (_forward);}
	Vector3 right(){return (_right);}
	Vector3 up(){return (_up);}

	vector<Vector3> &vertices(){return (_vertices);}
	vector<Vector2> &uvs(){return (_uvs);}
	vector<Vector3> &normales(){return (_normales);}
	vector<Face> &faces(){return (_faces);}
	Face *faces(size_t i){if (i >= _faces.size())return (NULL);return (&(_faces[i]));}

	void add_component(c_mesh *mesh){add_component(mesh, mesh->pos());}
	void add_component(c_mesh *mesh, Vector3 pos);
	void add_point(Vector3 p_point){_vertices.push_back(p_point);}
	void add_uv(Vector2 p_uv){_uvs.push_back(p_uv);}
	void add_normale(Vector3 p_normale){_normales.push_back(p_normale);}
	void add_face(Face p_face){_faces.push_back(p_face);}
	void set_texture(c_image *p_texture){_texture = p_texture;}
	void set_texture(c_tileset *p_texture){set_texture(p_texture->image());}
	void set_transparency(float p_transparency){_transparency = p_transparency;}
	void compute_normales();
	void compute_bubble_box();
	void compute_axis();

	void set_kinetic(bool p_kinetic){_kinetic = p_kinetic;}

	void bake();

	void look_at(Vector3 target);
	void rotate_around_point(Vector3 target, Vector3 delta);
	void rotate(Vector3 delta);
	void move(Vector3 delta){_pos += delta;}
	void add_velocity(Vector3 delta){_velocity += delta;}
	void apply_velocity(){move(_velocity);}
	void reset_velocity(){_velocity = 0;}
	void set_velocity(Vector3 p_velocity){_velocity = p_velocity;}
	void place(Vector3 p_pos){_pos = p_pos;}

	void render_color(c_camera *camera){render_color_differed(camera, pos());}
	void render_texture(c_camera *camera){render_texture_differed(camera, pos());}
	void render_color_differed(c_camera *camera, Vector3 p_pos);
	void render_texture_differed(c_camera *camera, Vector3 p_pos);
	void render(c_camera *camera){render_differed(camera, pos());}
	void render_differed(c_camera *camera, Vector3 p_pos);
};

c_mesh *primitive_cube(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake = true);

c_mesh *primitive_voxel(Vector3 pos, c_tileset *tileset, Vector2 top_sprite, Vector2 side_sprite, Vector2 down_sprite, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
c_mesh *primitive_voxel(Vector3 pos, c_tileset *tileset, size_t type, float p_transparency = 1.0f, bool should_bake = false, Vector3 rot = 0, Vector3 size = 1);
c_mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector2 size, Color color, bool should_bake = true);
c_mesh *primitive_plane(Vector3 pos, Vector3 rot, Vector3 size, Color color, bool should_bake = true);

#endif
