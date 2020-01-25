#ifndef JGL_MESH_H
#define JGL_MESH_H

struct Face
{
	Color color;
	int index_vertices[3];
	int index_uvs[3];
	Vector3 normale;

	Face(int p_index_vertices[3], int p_index_uvs[3], Color p_color = Color(190, 190, 190))
	{
		for (size_t i = 0; i < 3; i++)
		{
			index_vertices[i] = p_index_vertices[i];
			index_uvs[i] = p_index_uvs[i];
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
	GLuint _alpha_buffer;

	Vector3 _pos;
	Vector3 _size;

	Vector3 _rotation;
	Vector3 _forward;
	Vector3 _right;
	Vector3 _up;

	vector<Face>	_faces;

	vector<Vector3>	_vertices;
	vector<Vector2>	_uvs;

	vector<Vector3>	_baked_vertices;
	vector<Vector2>	_baked_uvs;
	vector<Color>	_baked_colors;
	vector<Vector3>	_baked_normales;

	c_image *_texture;

public:
	c_mesh(Vector3 p_pos);

	Vector3 pos(){return (_pos);}
	Vector3 size(){return (_size);}
	Vector3 rotation(){return (_rotation);}
	Vector3 forward(){return (_forward);}
	Vector3 right(){return (_right);}
	Vector3 up(){return (_up);}

	vector<Vector3> &vertices(){return (_vertices);}
	vector<Vector2> &uvs(){return (_uvs);}
	vector<Face> &faces(){return (_faces);}

	void add_point(Vector3 p_point);
	void add_uv(Vector2 p_uv);
	void add_face(Face p_face);
	void set_texture(c_image *p_texture);
	void compute_normales();
	void compute_axis();

	void bake();

	void look_at(Vector3 target);
	void rotate_around_point(Vector3 target, Vector3 delta);
	void rotate(Vector3 delta);
	void move(Vector3 delta);
	void place(Vector3 p_pos);

	void render(Matrix &MVP);
};

c_mesh *primitive_cube(Vector3 pos, Vector3 size, Color color);
#endif
