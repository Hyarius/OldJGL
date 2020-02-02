#ifndef JGL_FIRST_PERSON_CONTROLER_H
#define JGL_FIRST_PERSON_CONTROLER_H

#include "jgl_widgets.h"
#include "jgl_widget_component.h"

class c_first_person_controler : public c_widget
{
private:
	float _move_speed;
	float _rot_speed;
	c_camera *_camera;
	vector<c_mesh *> _meshes;

public:
	c_first_person_controler(c_widget *p_parent = nullptr);

	c_mesh *add_mesh(c_mesh *p_mesh){_meshes.push_back(p_mesh);return (_meshes.back());}

	bool handle_keyboard();
	bool handle_mouse();
	void set_geometry_imp(Vector2 p_anchor, Vector2 p_area);
	void render();
};

#endif
