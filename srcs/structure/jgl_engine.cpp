#include "jgl.h"

c_engine::c_engine()
{
	_meshes.clear();
}

void c_engine::handle_physics()
{
	bool found;
	c_mesh *tmp;

	for (size_t i = 0; i < _meshes.size(); i++)
	{
		tmp = mesh(i);
		if (tmp->kinetic() == true)
		{
			found = false;
			for (size_t j = 0; j < _meshes.size(); j++)
			{
				if (j != i && intersect_bubble_box(tmp, mesh(j)) == true && intersect_mesh(tmp, mesh(j)) == true)
					found = true;
			}

			if (found == false)
				tmp->add_velocity(Vector3(0.0f, -0.001f, 0.0f) * g_application->fps_ratio());
			else
			{
				tmp->add_velocity(Vector3(tmp->velocity().x * -0.9f, tmp->velocity().y * -0.9f, tmp->velocity().z * -0.9f));
			}
		}
	}
	for (size_t i = 0; i < _meshes.size(); i++)
	{
		tmp = mesh(i);
		if (tmp->kinetic() == true)
			tmp->apply_velocity();
	}
}
