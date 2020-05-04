#ifndef JGL_ENGINE_H
#define JGL_ENGINE_H

namespace jgl
{
	class Engine
	{
	protected:
		std::vector<jgl::Mesh*> _meshes;

	public:
		Engine();

		Mesh* add_mesh(Mesh* p_mesh) { _meshes.push_back(p_mesh); return (p_mesh); }

		std::vector<Mesh*>& meshes() { return (_meshes); }
		Mesh* mesh(size_t i) { if (i >= _meshes.size())return (NULL); return (_meshes[i]); }

		void handle_physics();
	};
}
#endif
