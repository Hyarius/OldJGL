#ifndef JGL_ENGINE_H
#define JGL_ENGINE_H

class c_engine :
{
private:
	vector<c_mesh *> _meshes;
public:
	c_engine();
	c_mesh *add_mesh(c_mesh *p_mesh);
}

#endif
