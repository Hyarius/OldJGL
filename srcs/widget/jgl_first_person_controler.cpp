#include "jgl.h"

c_first_person_controler::c_first_person_controler(c_widget *p_parent) : c_widget(p_parent)
{
	SDL_ShowCursor(SDL_DISABLE);
	_camera = new c_camera(Vector3(0.0f, 0.0f, 0.0f), 45, 0.1f, 100.0f);
	_camera->look_at(Vector3(0, 10, 0));
	_move_speed = 0.05f;
	_rot_speed = 0.1f;
	_engine = new c_engine();
}

void c_first_person_controler::set_geometry_imp(Vector2 p_anchor, Vector2 p_area)
{

}

void c_first_person_controler::render()
{
	_viewport->use();
	glClear(GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < _engine->meshes().size(); i++)
		if (_engine->mesh(i)->transparency() == 1.0f)
			_engine->mesh(i)->render(_camera);

	for (size_t i = 0; i < _engine->meshes().size(); i++)
		if (_engine->mesh(i)->transparency() != 1 && _engine->mesh(i)->transparency() != 0)
			_engine->mesh(i)->render(_camera);
}

bool c_first_person_controler::handle_keyboard()
{
	bool action = false;

	if (get_keyboard()->get_key(SDL_SCANCODE_ESCAPE) == key_state::down)
	{
		g_application->quit();
		return (true);
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_W) == key_state::down)
	{
		_camera->move(_camera->forward() * Vector3(1, 0, 1) * -_move_speed * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_S) == key_state::down)
	{
		_camera->move(_camera->forward() * Vector3(1, 0, 1) * _move_speed * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_D) == key_state::down)
	{
		_camera->move(_camera->right() * _move_speed * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_A) == key_state::down)
	{
		_camera->move(_camera->right() * -_move_speed * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_E) == key_state::down)
	{
		_camera->rotate(1 * g_application->fps_ratio(), 0 * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_Q) == key_state::down)
	{
		_camera->rotate(-1 * g_application->fps_ratio(), 0 * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_LSHIFT) == key_state::down)
	{
		_camera->move(Vector3(0, -1, 0) * _move_speed * g_application->fps_ratio());
		action = true;
	}
	if (get_keyboard()->get_key(SDL_SCANCODE_SPACE) == key_state::down)
	{
		_camera->move(Vector3(0, 1, 0) * _move_speed * g_application->fps_ratio());
		action = true;
	}

	return (action);
}

bool c_first_person_controler::handle_mouse()
{
	Vector2 rel_pos = get_mouse()->rel_pos;

	if (rel_pos != 0)
	{
		_camera->rotate(_rot_speed * rel_pos.x, _rot_speed * rel_pos.y);
		get_mouse()->place(g_application->size() / 2);
		return (true);
	}
	return (false);
}
