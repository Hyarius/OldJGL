#ifndef JGL_ENGINE_H
#define JGL_ENGINE_H

class c_engine
{
private:
	vector<c_mesh *> _meshes;

public:
	c_engine();

	c_mesh *add_mesh(c_mesh *p_mesh){_meshes.push_back(p_mesh);return (p_mesh);}

	vector<c_mesh *> &meshes(){return (_meshes);}
	c_mesh *mesh(size_t i){if (i >= _meshes.size())return (NULL);return (_meshes[i]);}

	void handle_physics();
};

#endif
