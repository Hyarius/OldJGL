#ifndef JGL_RENDER_WIDGET_H
#define JGL_RENDER_WIDGET_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

namespace jgl
{
	class Render_widget : public Widget
	{
	protected:
		Camera* _camera;

		Engine* _engine;

	public:
		Render_widget(Widget* p_parent = nullptr);

		Mesh* add_mesh(Mesh* p_mesh)
		{
			_engine->add_mesh(p_mesh);
			return (p_mesh);
		}

		Camera* camera() { return(_camera); }
		Engine* engine() { return(_engine); }

		void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
		void render();
	};
}

#endif
