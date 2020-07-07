#ifndef JGL_ENGINE_H
#define JGL_ENGINE_H

namespace jgl
{
	class Engine
	{
	protected:
		jgl::Array<jgl::Mesh*> _meshes;

	public:
		Engine();

		Mesh* add_mesh(Mesh* p_mesh) { _meshes.push_back(p_mesh); return (p_mesh); }

		jgl::Array<Mesh*>& meshes() { return (_meshes); }
		Mesh* mesh(size_t i) { if (i >= _meshes.size())return (NULL); return (_meshes[i]); }

		void handle_physics();
		void render(const jgl::Camera* camera);
	};
}
#endif
