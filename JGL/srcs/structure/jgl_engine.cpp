#include "jgl.h"

namespace jgl
{
	Engine::Engine()
	{
		_meshes.clear();
	}

	void Engine::handle_physics()
	{
		bool found;
		Mesh* tmp;

		for (uint32_t i = 0; i < _meshes.size(); i++)
		{
			tmp = mesh(i);
			if (tmp->kinetic() == true)
			{
				found = false;
				for (uint32_t j = 0; j < _meshes.size(); j++)
				{
					if (j != i && intersect_bubble_box(tmp, mesh(j)) == true)
						found = true;
				}

				if (found == false)
					tmp->add_velocity(Vector3(0.0f, -0.05f, 0.0f) * g_application->fps_ratio());
				else
					tmp->reset_velocity();
			}
		}
		for (uint32_t i = 0; i < _meshes.size(); i++)
		{
			tmp = mesh(i);
			if (tmp->kinetic() == true)
				tmp->apply_velocity();
		}
	}

	void Engine::render(const jgl::Camera *camera)
	{
		jgl::fill_rectangle(0, camera->viewport()->area(), jgl::Color(180, 180, 180), camera->viewport());
		for (uint32_t i = 0; i < _meshes.size(); i++)
		{
			_meshes[i]->render(camera);
		}
	}
}