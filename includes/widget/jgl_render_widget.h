#ifndef JGL_RENDER_WIDGET_H
#define JGL_RENDER_WIDGET_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_render_widget : public c_widget
{
private:
	c_camera *_camera;

	c_engine *_engine;

public:
	c_render_widget(c_widget *p_parent = nullptr);

	c_mesh *add_mesh(c_mesh *p_mesh)
	{
		_engine->add_mesh(p_mesh);
		return (p_mesh);
	}

	c_camera *camera(){return(_camera);}
	c_engine *engine(){return(_engine);}

	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void render();
};

#endif
