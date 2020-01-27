#include "jgl.h"

c_render_widget::c_render_widget(c_widget *p_parent) : c_widget(p_parent)
{
	_camera = new c_camera(Vector3(4.0f, 3.5f, 3.0f), 45, 0.1f, 100.0f);
	_camera->look_at(Vector3(0, 0, 0));
	_meshes.clear();
}

void c_render_widget::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

}

void c_render_widget::render()
{
	/*
	if (camera == nullptr)
	{
		camera = new c_camera(Vector3(4.0f, 3.5f, 3.0f), 45, 0.1f, 100.0f);
		camera->look_at(Vector3(0, 0, 0));

		mesh = primitive_cube(Vector3(0, 0, 0), Vector3(1, 1, 1), Color(255, 255, 255));
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	mesh->render(camera->MVP());
	*/

	_viewport->use();
	glClear(GL_DEPTH_BUFFER_BIT);

	Matrix MVP = _camera->MVP();

	for (size_t i = 0; i < _meshes.size(); i++)
		if (_meshes[i]->transparency() == 1.0f)
			_meshes[i]->render(_camera);

	for (size_t i = 0; i < _meshes.size(); i++)
		if (_meshes[i]->transparency() != 1 && _meshes[i]->transparency() != 0)
			_meshes[i]->render(_camera);

	for (size_t i = 0; i < _meshes.size(); i++)
		_meshes[i]->rotate(Vector3(0, 1, 1));

	// _camera->rotate_around_point(_meshes[0]->pos(), Vector3(0, 1, 0));
	// _camera->look_at(Vector3(0, 0, 0));
}
