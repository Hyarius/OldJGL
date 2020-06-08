#include "jgl.h"

namespace jgl
{
	Render_widget::Render_widget(Widget* p_parent) : Widget(p_parent)
	{
		_camera = new Camera(Vector3(4.0f, 3.5f, 3.0f), 45, 0.1f, 100.0f);
		_camera->look_at(Vector3(0, 0, 0));
		_engine = new Engine();
	}

	void Render_widget::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
	{

	}

	void Render_widget::render()
	{
		_viewport->use();

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() == 1.0f)
				_engine->mesh(i)->render(_camera);

		for (size_t i = 0; i < _engine->meshes().size(); i++)
			if (_engine->mesh(i)->transparency() != 1 && _engine->mesh(i)->transparency() != 0)
				_engine->mesh(i)->render(_camera);
	}
}